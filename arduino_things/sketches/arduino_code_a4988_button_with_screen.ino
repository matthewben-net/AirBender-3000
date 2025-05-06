#include "AccelStepper.h"
#include <Wire.h>
#include "HX711.h"

// Define stepper motor connections and motor interface type. 
#define enablePin 7
#define dirPin 6
#define stepPin 5
#define motorInterfaceType 1
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

// Variables to keep track of when the stepper motor was last moved, and how long it stays idle before disablement
unsigned long lastMoveTime = 0;
const unsigned long motorDisableDelay = 3000;  // 3 seconds after last move

// Motor Control
volatile int motorCommand = 0;
volatile bool commandReceived = false;

// HX711 instances
HX711 scale_drag;
HX711 scale_lift;

// Pins for HX711
const uint8_t dataPin_drag = 11;
const uint8_t clockPin_drag = 10;
const uint8_t dataPin_lift = 9;
const uint8_t clockPin_lift = 8;

// Calibration and unit conversion for forces
const float GRAMS_TO_NEWTONS = 0.00981;
volatile float drag_newtons = 0.0;
volatile float lift_newtons = 0.0;

// Pitot tube airspeed variables
const int sensorPin = A7;
const float rho = 1.204;  // Air density
const int offsetSamples = 10;
const int averageSamples = 20;
const int zeroSpan = 2;
const float adcToVolt = 1.0 / 1023.0;
const float scaleFactor = 10000.0 / rho;
float airspeed = 0.0;
int offset = 0;

// I2C data buffer: 4 bytes drag, 4 bytes lift, 4 bytes airspeed
uint8_t data_buffer[12];

void setup() {
  // Initialize HX711 scales
  scale_drag.begin(dataPin_drag, clockPin_drag);
  scale_lift.begin(dataPin_lift, clockPin_lift);
  scale_drag.set_offset(792489);
  scale_drag.set_scale(389.399719);
  scale_lift.set_offset(114174);
  scale_lift.set_scale(406.546539);
  scale_drag.tare();
  scale_lift.tare();

  // Initialize I2C communication
  Wire.begin(8);  // Set the Arduino's I2C address to 8
  Wire.onReceive(receiveData);  // Function to handle incoming stepper motor commands
  Wire.onRequest(requestEvent); // Function to handle data requests from ESP32

  // Stepper motor initialization
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); // Start enabled
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(1000);
  stepper.setMinPulseWidth(1);  // 1 microsecond for A4988

  // Airspeed sensor offset calibration
  int offsetSum = 0;
  for (int i = 0; i < offsetSamples; i++) {
    offsetSum += analogRead(sensorPin) - 512;
  }
  offset = offsetSum / offsetSamples;
}

void loop() {
  // I2C if statement to determine whether to move the stepper motor or reset the scales
  if (commandReceived) {
    noInterrupts();
    int command = motorCommand;
    commandReceived = false;
    interrupts();

    if (command == 1) {
      digitalWrite(enablePin, LOW);
      stepper.move(25);
    } else if (command == 2) {
      digitalWrite(enablePin, LOW);
      stepper.move(-25);
    } else if (command == 3) {
      scale_drag.tare();
      scale_lift.tare();
    } else if (command == 4) {
      calibrate_airspeed_sensor();
    }
  }

  // Logic to determine whether the stepper motor should be enabled or idle
  bool motorIsMoving = stepper.distanceToGo() != 0;
  if (motorIsMoving) {
    digitalWrite(enablePin, LOW);  // Keep motor energized
    lastMoveTime = millis();       // Reset timer
  }
  // Disable after delay only if it's done moving
  if (!motorIsMoving && (millis() - lastMoveTime > motorDisableDelay)) {
    digitalWrite(enablePin, HIGH); // Disable motor
  }

  // Runs stepper motor via AccelStepper
  stepper.run();

  // If loop to read the load cell data, convert it into newtons, measure and calculate the airspeed, and and set the buffer to the float needed for the ESP32 to recieve the calculated force and airspeed floats
  static unsigned long lastRead = 0;
  if (millis() - lastRead > 100) {
    // Force sensor readings
    float drag = scale_drag.get_units(1);
    float lift = scale_lift.get_units(1);
    drag_newtons = drag * GRAMS_TO_NEWTONS;
    lift_newtons = lift * GRAMS_TO_NEWTONS;

    // Airspeed calculation from pitot tube
    int adcSum = 0;
    for (int i = 0; i < averageSamples; i++) {
      adcSum += analogRead(sensorPin) - offset;
    }
    float adcAvg = adcSum / float(averageSamples);

    airspeed = 0.0;
    if (adcAvg < 512 - zeroSpan) {
      airspeed = -sqrt(-scaleFactor * (adcAvg * adcToVolt - 0.5));
    } else if (adcAvg > 512 + zeroSpan) {
      airspeed = sqrt(scaleFactor * (adcAvg * adcToVolt - 0.5));
    }

    // Safely update I2C data buffer
    noInterrupts();
    memcpy(data_buffer, &drag_newtons, 4);
    memcpy(data_buffer + 4, &lift_newtons, 4);
    memcpy(data_buffer + 8, &airspeed, 4);
    interrupts();

    lastRead = millis();
  }
}

// Function to recalibrate airspeed offset (use this if you accidentally started the airduino when the airflow wasn't at 0, but make sure there isn't any airflow when you run it)
void calibrate_airspeed_sensor() {
  int offsetSum = 0;
  for (int i = 0; i < offsetSamples; i++) {
    offsetSum += analogRead(sensorPin) - 512;
  }
  offset = offsetSum / offsetSamples;
}4

void receiveData(int byteCount) {
  while (Wire.available()) {
    motorCommand = Wire.read();
    commandReceived = true;
  }
}

void requestEvent() {
  Wire.write(data_buffer, 12);
}
