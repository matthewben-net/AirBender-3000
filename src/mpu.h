#ifndef MPU_H
#define MPU_H

#include <Arduino.h>

// MPU6050 I2C address
#define MPU_ADDRESS 0x69

// Function declarations
void mpu6050_init();
void read_mpu6050_angle();

#endif
