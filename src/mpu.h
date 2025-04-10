#ifndef MPU_H
#define MPU_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

// MPU6050 I2C address
extern uint8_t MPU_ADDRESS;

// Function declarations
void mpu6050_init();
void read_mpu6050_angle();

#ifdef __cplusplus
}
#endif

#endif
