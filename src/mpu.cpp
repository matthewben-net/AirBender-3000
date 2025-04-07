#include "mpu.h"
#include <Wire.h>

// Use external I2C bus declared in main.cpp
extern TwoWire myI2C;

void mpu6050_init() {
    myI2C.beginTransmission(MPU_ADDRESS);
    myI2C.write(0x6B);           // Power management register
    myI2C.write(0);              // Set to zero (wake up the sensor)
    myI2C.endTransmission();
}

void read_mpu6050_raw() {
    myI2C.beginTransmission(MPU_ADDRESS);
    myI2C.write(0x3B);  // Starting register for accelerometer data
    myI2C.endTransmission(false);  // Send repeated start

    myI2C.requestFrom(MPU_ADDRESS, 14);  // Read accel + temp + gyro

    if (myI2C.available() == 14) {
        int16_t ax = myI2C.read() << 8 | myI2C.read();
        int16_t ay = myI2C.read() << 8 | myI2C.read();
        int16_t az = myI2C.read() << 8 | myI2C.read();
        int16_t temp = myI2C.read() << 8 | myI2C.read();
        int16_t gx = myI2C.read() << 8 | myI2C.read();
        int16_t gy = myI2C.read() << 8 | myI2C.read();
        int16_t gz = myI2C.read() << 8 | myI2C.read();

        Serial.printf("Accel: ax=%d ay=%d az=%d | Gyro: gx=%d gy=%d gz=%d\n",
                      ax, ay, az, gx, gy, gz);
    }
}
