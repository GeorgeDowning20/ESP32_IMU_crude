#pragma once

#include "i2c.h"
#include "registers.h"
#include "i2c_config.h"

#define M_PI 3.14159265358979323846
#define ACCEL_SENSITIVITY 16384.0 // for ±2g
#define GYRO_SENSITIVITY 131.0 // for +- 250 degrees/sec
#define GYRO_SENSITIVITY_RADS (GYRO_SENSITIVITY* 180.0/M_PI)


typedef struct {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;

    float accel_x_g;
    float accel_y_g;
    float accel_z_g;
    float gyro_x_dps;
    float gyro_y_dps;
    float gyro_z_dps;
} mpu6050_data_t;



extern volatile mpu6050_data_t mpu6050_accel_gyro_data;
 

esp_err_t read_who_am_i(uint8_t* who_am_i);
esp_err_t read_gyro_data(uint8_t* gyro_data);
esp_err_t read_accel_gyro_data(uint8_t* sensor_data);
esp_err_t read_mpu6050_data(mpu6050_data_t* data);
esp_err_t readMPU(void);
esp_err_t calibrate_mpu6050(void);