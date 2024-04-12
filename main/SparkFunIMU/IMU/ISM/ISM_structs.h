
#ifndef ISM330DHCX_CONFIG_STRUCT_H
#define ISM330DHCX_CONFIG_STRUCT_H

#include "ISM_settings.h"
#include <stdint.h>

typedef struct {
    // Accelerometer Settings
    unsigned char acc_odr;         // Output Data Rate
    unsigned char acc_fs;          // Full-Scale Selection
    // Gyroscope Settings
    unsigned char gyro_odr;        // Output Data Rate
    unsigned char gyro_fs;         // Full-Scale Selection
    // FIFO Settings
    unsigned char fifo_mode;       // FIFO Mode
    unsigned short fifo_threshold; // FIFO Threshold
    // Interrupt Settings
    unsigned char int1_config;     // INT1 Configuration
    unsigned char int2_config;     // INT2 Configuration
} ISM330DHCX_ConfigTypeDef;

typedef struct {
    // Accelerometer Data
    uint8_t OUT_TEMP_L;
    uint8_t OUT_TEMP_H;

    uint8_t OUTX_L_G;
    uint8_t OUTX_H_G;
    uint8_t OUTY_L_G;
    uint8_t OUTY_H_G;
    uint8_t OUTZ_L_G;
    uint8_t OUTZ_H_G;

    uint8_t OUTX_L_A;
    uint8_t OUTX_H_A;
    uint8_t OUTY_L_A;
    uint8_t OUTY_H_A;
    uint8_t OUTZ_L_A;
    uint8_t OUTZ_H_A;
} ISM330DHCX_OutputDataTypeDef;

typedef struct {
    // Accelerometer Data
    float accel_x;
    float accel_y;
    float accel_z;
    // Gyroscope Data
    float gyro_x;
    float gyro_y;
    float gyro_z;
    // Temperature Data
    float temp;
} ISM330DHCX_DataTypeDef;


#endif // ISM330DHCX_CONFIG_STRUCT_H
