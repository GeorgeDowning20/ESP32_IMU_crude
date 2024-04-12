#pragma once

#include "MMC_registers.h"
#include "MMC_settings.h"
#include "MMC_structs.h"

#include "../../../IMU_I2c/IMU_I2c.hpp"

#include "esp_err.h"

class MMC
{
public:

    // MMC(IMU_I2C &i2c);
    MMC(){};

    esp_err_t init(IMU_I2C *i2c);
    esp_err_t read();
    esp_err_t SetConfig(MMC5983MA_ConfigTypeDef config);

    esp_err_t WhoAmI();
    esp_err_t reset();

    esp_err_t init();

    void Verbose();

    IMU_I2C *I2c;
    MMC5983MA_ConfigTypeDef config;
    MMC5983MA_OutputDataTypeDef raw;
    MMC5983MA_DataTypeDef data;

    const float lsbtoGauss = 1 / 16384;

private:
    MMC5983MA_ConfigTypeDef getDefaultConfig();
};