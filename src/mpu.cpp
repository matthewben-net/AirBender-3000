#include "mpu.h"
#include "ui/vars.h"
#include <Wire.h>

// Use external I2C bus declared in main.cpp
extern TwoWire myI2C;

const uint8_t MPU_ADDRESS = 0x68;

// Toggle debug logging (1 = enabled, 0 = disabled)
#define DEBUG 0

void mpu6050_init() {
    myI2C.beginTransmission(MPU_ADDRESS);
    myI2C.write(0x6B);  // Power management register
    myI2C.write(0);     // Wake up sensor
    myI2C.endTransmission();
}

void read_mpu6050_angle() {
    myI2C.beginTransmission(MPU_ADDRESS);
    myI2C.write(0x3B);  // Starting register for accelerometer data
    myI2C.endTransmission(false);
    myI2C.requestFrom((uint8_t)MPU_ADDRESS, (uint8_t)6);

    if (myI2C.available() == 6) {
        int16_t ax = myI2C.read() << 8 | myI2C.read();
        int16_t ay = myI2C.read() << 8 | myI2C.read();
        int16_t az = myI2C.read() << 8 | myI2C.read();

        // Convert only ax to G; ay and az used directly in formula
        float ax_g = ax / 16384.0;
        float angleY = atan2(ax_g, sqrt((float)(ay * ay + az * az)) / 16384.0) * 180.0 / PI;

        // Apply static offset correction
        float calibratedAngleY = angleY - 3.55;

        // Set the float variable for bar graph
        set_var_float_mpu_angle_number(calibratedAngleY);

        // Format and store the angle
		char angle_str[100];
		snprintf(angle_str, sizeof(angle_str), "%.2f Degrees", calibratedAngleY);
		set_var_string_mpu_angle_data(angle_str);

#if DEBUG
    // If debugging, don't forget to add   Serial.begin(115200); in the main.cpp void setup() function
    Serial.printf("Y Angle: %s\n", angle_str);
#endif
    }
}