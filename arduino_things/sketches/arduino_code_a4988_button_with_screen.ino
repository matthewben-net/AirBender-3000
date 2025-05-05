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

// Calibration and unit conversion
const float GRAMS_TO_NEWTONS = 0.00981;
volatile float drag_newtons = 0.0;
volatile float lift_newtons = 0.0;
uint8_t force_data_buffer[8];  // Store pre-converted force data

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
  Wire.onReceive(receiveData);  // Set up a function to handle incoming stepper motor controls
  Wire.onRequest(requestEvent); // New function to handle data requests

  // Stepper motor initialization
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); // Start enabled
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(1000);
  stepper.setMinPulseWidth(1);  // 1 microsecond for A4988
}

void loop() {
  // I2C command if statement to determine whether to move the stepper motor or reset the scales
  if (commandReceived) {
    noInterrupts();  // Safely access shared variables
    int command = motorCommand;
    commandReceived = false;
    interrupts();

  if (command == 1) {
    digitalWrite(enablePin, LOW);
    stepper.move(25);
  } else if (command == 2) {
      stepper.move(-25);
      digitalWrite(enablePin, LOW);
  } else if (command ==3 ) {
      scale_drag.tare();
      scale_lift.tare();
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
  
  // If loop to read the load cell data, convert it into newtons, and set the buffer to the float needed for the ESP32 to recieve the calculated force floats
  static unsigned long lastRead = 0;
  if (millis() - lastRead > 100) {
    float drag = scale_drag.get_units(1);
    float lift = scale_lift.get_units(1);
    drag_newtons = drag * GRAMS_TO_NEWTONS;
    lift_newtons = lift * GRAMS_TO_NEWTONS;

    // Safely update buffer
    noInterrupts();
    memcpy(force_data_buffer, &drag_newtons, 4);
    memcpy(force_data_buffer + 4, &lift_newtons, 4);
    interrupts();
    lastRead = millis();
  }
}

void receiveData(int byteCount) {
  while (Wire.available()) {
    motorCommand = Wire.read();
    commandReceived = true;
  }
}

void requestEvent() {
  Wire.write(force_data_buffer, 8);  // Respond instantly
}
