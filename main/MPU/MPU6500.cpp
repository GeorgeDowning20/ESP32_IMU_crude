// #include "MPU6500.hpp"



// esp_err_t MPU6500::WhoAmI()
// {
//     uint8_t who_am_i;
//     esp_err_t ret = mpu.read(I2C_MASTER_NUM, MPU_6050_ADDR, MPU6050_WHO_AM_I, &who_am_i, 1);
//     if (ret != ESP_OK)
//         return ret;
//     printf("WHO_AM_I: 0x%02x\n", who_am_i);
//     return ret;
// }

// // void MPU6500::init(){

// //     config.fchoice_b = MPU6050_FCHOICE_B_0;
// //     config.dlpf_cfg = MPU6050_DLPF_CFG_0;
// //     config.gyro_fs_sel = MPU6050_GYRO_FS_SEL_500;

// //     config.accel_fchoice_b = MPU6050_ACCEL_FCHOICE_B_0;
// //     config.accel_dlpf_cfg = MPU6050_A_DLPF_CFG_0;
// //     config.accel_fs_sel = MPU6050_ACCEL_FS_SEL_4G;
// //     return;

// // }

// void MPU6500::setConfig()
// {
//     uint8_t Configuration = 0;
//     Configuration |= static_cast<uint8_t>(config.accel_dlpf_cfg);
//     mpu.write(I2C_MASTER_NUM, MPU_6050_ADDR, MPU6050_CONFIG, &Configuration, 1);

//     uint8_t Gyroscope_Configuration = 0;
//     Gyroscope_Configuration |= static_cast<uint8_t>(config.fchoice_b);
//     Gyroscope_Configuration |= static_cast<uint8_t>(config.gyro_fs_sel) << 3;
//     mpu.write(I2C_MASTER_NUM, MPU_6050_ADDR, MPU6050_GYRO_CONFIG, &Gyroscope_Configuration, 1);

//     uint8_t Accelerometer_Configuration = 0;
//     Accelerometer_Configuration |= static_cast<uint8_t>(config.accel_fs_sel) << 3;
//     mpu.write(I2C_MASTER_NUM, MPU_6050_ADDR, MPU6050_ACCEL_CONFIG, &Accelerometer_Configuration, 1);

//     uint8_t Accelerometer_Configuration_2 = 0;
//     Accelerometer_Configuration_2 |= static_cast<uint8_t>(config.accel_dlpf_cfg);
//     Accelerometer_Configuration_2 |= static_cast<uint8_t>(config.accel_fchoice_b) << 3;

//     switch (config.gyro_fs_sel)
//     {
//         case MPU6050_GYRO_FS_SEL_250:
//             calibration.gyro_x = MPU6050_GYRO_FS_SEL_250_SENSITIVITY_RAD;
//             calibration.gyro_y = MPU6050_GYRO_FS_SEL_250_SENSITIVITY_RAD;
//             calibration.gyro_z = MPU6050_GYRO_FS_SEL_250_SENSITIVITY_RAD;
//             break;
        
//         case MPU6050_GYRO_FS_SEL_500:
//             calibration.gyro_x = MPU6050_GYRO_FS_SEL_500_SENSITIVITY_RAD;
//             calibration.gyro_y = MPU6050_GYRO_FS_SEL_500_SENSITIVITY_RAD;
//             calibration.gyro_z = MPU6050_GYRO_FS_SEL_500_SENSITIVITY_RAD;
//             break;

//         case MPU6050_GYRO_FS_SEL_1000:
//             calibration.gyro_x = MPU6050_GYRO_FS_SEL_1000_SENSITIVITY_RAD;
//             calibration.gyro_y = MPU6050_GYRO_FS_SEL_1000_SENSITIVITY_RAD;
//             calibration.gyro_z = MPU6050_GYRO_FS_SEL_1000_SENSITIVITY_RAD;
//             break;

//         case MPU6050_GYRO_FS_SEL_2000:
//             calibration.gyro_x = MPU6050_GYRO_FS_SEL_2000_SENSITIVITY_RAD;
//             calibration.gyro_y = MPU6050_GYRO_FS_SEL_2000_SENSITIVITY_RAD;
//             calibration.gyro_z = MPU6050_GYRO_FS_SEL_2000_SENSITIVITY_RAD;
//             break;

//     }

//     switch (config.accel_fs_sel)
//     {
//     case MPU6050_ACCEL_FS_SEL_2G:
//         calibration.accel_x = MPU6050_ACCEL_FS_SEL_2G_SENSITIVITY_M_S2;
//         calibration.accel_y = MPU6050_ACCEL_FS_SEL_2G_SENSITIVITY_M_S2;
//         calibration.accel_z = MPU6050_ACCEL_FS_SEL_2G_SENSITIVITY_M_S2;
//         break;

//     case MPU6050_ACCEL_FS_SEL_4G:
//         calibration.accel_x = MPU6050_ACCEL_FS_SEL_4G_SENSITIVITY_M_S2;
//         calibration.accel_y = MPU6050_ACCEL_FS_SEL_4G_SENSITIVITY_M_S2;
//         calibration.accel_z = MPU6050_ACCEL_FS_SEL_4G_SENSITIVITY_M_S2;
//         break;

//     case MPU6050_ACCEL_FS_SEL_8G:
//         calibration.accel_x = MPU6050_ACCEL_FS_SEL_8G_SENSITIVITY_M_S2;
//         calibration.accel_y = MPU6050_ACCEL_FS_SEL_8G_SENSITIVITY_M_S2;
//         calibration.accel_z = MPU6050_ACCEL_FS_SEL_8G_SENSITIVITY_M_S2;
//         break;

//     case MPU6050_ACCEL_FS_SEL_16G:
//         calibration.accel_x = MPU6050_ACCEL_FS_SEL_16G_SENSITIVITY_M_S2;
//         calibration.accel_y = MPU6050_ACCEL_FS_SEL_16G_SENSITIVITY_M_S2;
//         calibration.accel_z = MPU6050_ACCEL_FS_SEL_16G_SENSITIVITY_M_S2;
//         break;

//     }
    
//     return 
// }

// esp_err_t MPU6500::readAll()
// {

//     uint8_t sensor_data[14];
//     esp_err_t ret = mpu.read(I2C_MASTER_NUM, MPU_6050_ADDR, MPU6050_ACCEL_XOUT_H, sensor_data, 14);

//     data.accel_x = (sensor_data[0] << 8) | sensor_data[1];
//     data.accel_y =(sensor_data[2] << 8) | sensor_data[3];
//     data.accel_z = (sensor_data[4] << 8) | sensor_data[5];
//     data.gyro_x = (sensor_data[8] << 8) | sensor_data[9];
//     data.gyro_y = (sensor_data[10] << 8) | sensor_data[11];
//     data.gyro_z = (sensor_data[12] << 8) | sensor_data[13];

//     buff.accel_x /= calibration.accel_x;
//     buff.accel_y /= calibration.accel_y;
//     buff.accel_z /= calibration.accel_z;
//     data.gyro_x /= calibration.gyro_x;
//     data.gyro_y /= calibration.gyro_y;
//     data.gyro_z /= calibration.gyro_z;


//     data.gyro_x -= offsets.gyro_x;
//     data.gyro_y -= offsets.gyro_y;
//     data.gyro_z -= offsets.gyro_z;

//     data.accel_x = rotation[0].accel_x * buff.accel_x 
//                  + rotation[0].accel_y * buff.accel_y 
//                  + rotation[0].accel_z * buff.accel_z;

//     data.accel_y = rotation[1].accel_x * buff.accel_x 
//                  + rotation[1].accel_y * buff.accel_y 
//                  + rotation[1].accel_z * buff.accel_z;

//     data.accel_z = rotation[2].accel_x * buff.accel_x 
//                  + rotation[2].accel_y * buff.accel_y 
//                  + rotation[2].accel_z * buff.accel_z;
// } 

// #define CALIBRATION_READINGS 1000


// esp_err_t MPU6500::calabrate()
// {
//     double ax, ay, az, gx, gy, gz;
//     double Sax, Say, Saz, Sgx, Sgy, Sgz;

//     for (int i = 0; i < CALIBRATION_READINGS; i++) {
//         esp_err_t ret = readAll();
//         if (ret != ESP_OK) {
//             return ret;
//         }

//         gx += data.gyro_x;
//         gy += data.gyro_y;
//         gz += data.gyro_z;

//         ax += data.accel_x;
//         ay += data.accel_y;
//         az += data.accel_z;

//         vTaskDelay(1); // delay for 1ms
//     }

//     offsets.gyro_x = gx / CALIBRATION_READINGS;
//     offsets.gyro_y = gy / CALIBRATION_READINGS;
//     offsets.gyro_z = gz / CALIBRATION_READINGS;

//     double avg_accel[3];

//     avg_accel[0] = ax / CALIBRATION_READINGS;
//     avg_accel[1] = ay / CALIBRATION_READINGS;
//     avg_accel[2] = az / CALIBRATION_READINGS;

//     // calulate the rotaion matrix given as rotataion[3]

    


//     return ESP_OK;
// }