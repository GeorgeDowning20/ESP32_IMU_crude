#pragma once

#include <stdint.h>


// MMC5983MA configuration structure
typedef struct {
    unsigned char bandwidth; // Output data resolution
    unsigned char continuousModeFreq; // Continuous measurement mode frequency
    unsigned char periodicSetFreq; // Periodic SET operation frequency
} MMC5983MA_ConfigTypeDef;

typedef struct{
    uint8_t xout0;
    uint8_t xout1;

    uint8_t yout0;
    uint8_t yout1;

    uint8_t zout0;
    uint8_t zout1;

    uint8_t xyzout2;
} MMC5983MA_OutputDataTypeDef;

typedef struct
{
    float mag_x;
    float mag_y;
    float mag_z;
} MMC5983MA_DataTypeDef;

typedef struct 
{
    uint8_t reg_0;
    uint8_t reg_1;
    uint8_t reg_2;
    uint8_t reg_3;
} MMC5983MA_CtrlRegTypeDef;
