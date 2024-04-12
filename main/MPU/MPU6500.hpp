#include "../IMU_I2c/IMU_I2c.hpp"
#include "registers.h"


typedef struct MPU6050_data_f{
    float accel_x;
    float accel_y;
    float accel_z;
    float temp;
    float gyro_x;
    float gyro_y;
    float gyro_z;
} MPU6050_data_f_t;


typedef struct MPU6050_config {
    MPU6050_FCHOICE_B fchoice_b;
    MPU6050_DLPF_CFG dlpf_cfg;
    MPU6050_GYRO_FS_SEL gyro_fs_sel;

    MPU6050_ACCEL_FCHOICE_B accel_fchoice_b;
    MPU6050_ACCEL_DLPF_CFG accel_dlpf_cfg;
    MPU6050_ACCEL_FS_SEL accel_fs_sel;
} MPU6050_config_t;


class MPU6500
{
public:
    MPU6500() { };

    esp_err_t  init();

    esp_err_t readAll();
    esp_err_t calibrate();
    

    void setConfig();
    esp_err_t setSleepEnabled(bool enabled);
    
    esp_err_t WhoAmI();
    esp_err_t reset();

    IMU_I2C mpu;
    MPU6050_config_t config;
    MPU6050_data_f_t data, offsets, calibration, variance, rotation[3], buff;

    esp_err_t calabrate();

    private:

    void changeEndian(void);
};


