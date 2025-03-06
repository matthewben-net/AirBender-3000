#include "AccelStepper.h"
#include <Wire.h>

// Define stepper motor connections and motor interface type. 
// Motor interface type must be set to 1 when using a driver
#define dirPin 2
#define stepPin 3
// Enable pin only required for TMC2208; ignore if necessary
#define EN_PIN 10    // LOW: Driver enabled, HIGH: Driver disabled

#define motorInterfaceType 1

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  // Initialize I2C communication
  Wire.begin(8);  // Set the Arduino's I2C address to 8
  Wire.onReceive(receiveData);  // Set up a function to handle incoming data

  // Set the maximum speed and acceleration:
  stepper.setMaxSpeed(3000);
  stepper.setAcceleration(1600);
  // Configure TMC2208 if needed
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);   // Enable the driver
}

void loop() {
  stepper.run();
}

// Function to handle incoming I2C data
void receiveData(int byteCount) {
  while (Wire.available()) {
    int command = Wire.read();  // Read the received command

    // Perform actions based on the received command
    if (command == 1) {
      // Command for clockwise rotation
      stepper.move(25);  // Move stepper clockwise
    } else if (command == 2) {
      // Command for counter-clockwise rotation
      stepper.move(-25);  // Move stepper counter-clockwise
    }
  }
}
