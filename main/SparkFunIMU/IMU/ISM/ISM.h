#pragma once

#include "ISM_registers.h"
#include "ISM_settings.h"
#include "ISM_structs.h"

#include "../../../IMU_I2c/IMU_I2c.hpp"
// #include <IMU_I2c.hpp>

#include "esp_err.h"

class ISM
{
public:
    ISM(){};

    esp_err_t init(IMU_I2C *i2c);
    esp_err_t read();
    esp_err_t SetConfig();

    esp_err_t WhoAmI();
    esp_err_t reset();

    void Verbose();

    IMU_I2C *I2c;
    ISM330DHCX_ConfigTypeDef config;
    ISM330DHCX_OutputDataTypeDef raw;
    ISM330DHCX_DataTypeDef data;

private:
    ISM330DHCX_ConfigTypeDef getDefaultConfig();
};