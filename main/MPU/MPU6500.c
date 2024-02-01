#include "MPU6500.h"
#include "i2c.h"

// read who am i register

volatile mpu6050_data_t mpu6050_accel_gyro_data;
mpu6050_data_t offsets;


inline esp_err_t read_who_am_i(uint8_t* who_am_i) {
    return i2c_master_read_device(I2C_NUM_0, MPU_6050_ADDR, MPU6050_WHO_AM_I, who_am_i, 1);
}

inline esp_err_t read_gyro_data(uint8_t* gyro_data) {
    // Gyroscope data registers start at MPU6050_GYRO_XOUT_H and there are 6 of them
    return i2c_master_read_device(I2C_NUM_0, MPU_6050_ADDR, MPU6050_GYRO_XOUT_H, gyro_data, 6);
}

inline esp_err_t read_accel_data(uint8_t* accel_data) {
    // Accelerometer data registers start at MPU6050_ACCEL_XOUT_H and there are 6 of them
    return i2c_master_read_device(I2C_NUM_0, MPU_6050_ADDR, MPU6050_ACCEL_XOUT_H, accel_data, 6);
}

inline esp_err_t read_accel_gyro_data(uint8_t* sensor_data) {
    // Accelerometer and gyroscope data registers start at MPU6050_ACCEL_XOUT_H and there are 14 of them
    return i2c_master_read_device(I2C_NUM_0, MPU_6050_ADDR, MPU6050_ACCEL_XOUT_H, sensor_data, 14);
}

esp_err_t read_mpu6050_data(mpu6050_data_t* data) {
    uint8_t sensor_data[14];
    esp_err_t ret = read_accel_gyro_data(sensor_data);
    if (ret != ESP_OK) {
        return ret;
    }

    data->accel_x = (sensor_data[0] << 8) | sensor_data[1];
    data->accel_y =(sensor_data[2] << 8) | sensor_data[3];
    data->accel_z = (sensor_data[4] << 8) | sensor_data[5];
    data->gyro_x = (sensor_data[8] << 8) | sensor_data[9];
    data->gyro_y = (sensor_data[10] << 8) | sensor_data[11];
    data->gyro_z = (sensor_data[12] << 8) | sensor_data[13];

    data->accel_x -= offsets.accel_x;
    data->accel_y -= offsets.accel_y;
    data->accel_z -= offsets.accel_z;
    data->gyro_x -= offsets.gyro_x;
    data->gyro_y -= offsets.gyro_y;
    data->gyro_z -= offsets.gyro_z;


    data->accel_x_g = data->accel_x / ACCEL_SENSITIVITY;
    data->accel_y_g = data->accel_y / ACCEL_SENSITIVITY;
    data->accel_z_g = data->accel_z / ACCEL_SENSITIVITY;

    data->gyro_x_dps = data->gyro_x / GYRO_SENSITIVITY_RADS;
    data->gyro_y_dps = data->gyro_y / GYRO_SENSITIVITY_RADS;
    data->gyro_z_dps = data->gyro_z / GYRO_SENSITIVITY_RADS;

    return ESP_OK;
}

esp_err_t readMPU(void)
{
    return read_mpu6050_data(&mpu6050_accel_gyro_data);
}


#define CALIBRATION_READINGS 1000

esp_err_t calibrate_mpu6050(void) {
    mpu6050_data_t data;
    int32_t sum_accel_x = 0, sum_accel_y = 0, sum_accel_z = 0;
    int32_t sum_gyro_x = 0, sum_gyro_y = 0, sum_gyro_z = 0;


    // set gyro to +- 350 degrees/sec

    uint8_t gyro_config = 0x00;
    esp_err_t ret = i2c_master_write_device(I2C_NUM_0, MPU_6050_ADDR, MPU6050_GYRO_CONFIG, &gyro_config, 1);
    if (ret != ESP_OK) {
        return ret;
    }

    for (int i = 0; i < CALIBRATION_READINGS; i++) {
        esp_err_t ret = read_mpu6050_data(&data);
        if (ret != ESP_OK) {
            return ret;
        }

        sum_accel_x += data.accel_x;
        sum_accel_y += data.accel_y;
        sum_accel_z += data.accel_z - ACCEL_SENSITIVITY; // assuming the device is flat, the z-axis should read 1g
        sum_gyro_x += data.gyro_x;
        sum_gyro_y += data.gyro_y;
        sum_gyro_z += data.gyro_z;

        vTaskDelay(1); // delay for 1ms
    }

    offsets.accel_x = sum_accel_x / CALIBRATION_READINGS;
    offsets.accel_y = sum_accel_y / CALIBRATION_READINGS;
    offsets.accel_z = sum_accel_z / CALIBRATION_READINGS;
    offsets.gyro_x = sum_gyro_x / CALIBRATION_READINGS;
    offsets.gyro_y = sum_gyro_y / CALIBRATION_READINGS;
    offsets.gyro_z = sum_gyro_z / CALIBRATION_READINGS;

    return ESP_OK;
}
