#include "MMC.h"
#include "math.h"

// MMC::MMC(IMU_I2C &i2c) : I2c(i2c)
// {
//     MMC5983MA_ConfigTypeDef config = getDefaultConfig();
//     SetConfig(config);
// }

esp_err_t MMC::init(IMU_I2C *i2c)
{
    I2c = i2c;
    MMC5983MA_ConfigTypeDef config = getDefaultConfig();
    SetConfig(config);
    return ESP_OK;
}


esp_err_t MMC::WhoAmI()
{
    uint8_t sensor_data[1];
    I2c->read(MMC5983MA_DEVICE_ID, MMC5983MA_PRODUCT_ID, sensor_data, 1);
    printf("WHO_AM_I: 0x%02x\n", sensor_data[0]);
    return ESP_OK;
}

esp_err_t MMC::read()
{
    I2c->read(MMC5983MA_DEVICE_ID, MMC5983MA_XOUT0, (uint8_t *)&raw, sizeof(MMC5983MA_OutputDataTypeDef));

    data.mag_x = ((raw.xout0 << 10) | (raw.xout1 << 2) | ((raw.xyzout2 >> 6) & 0x03)) - 0x20000;
    data.mag_y = ((raw.yout0 << 10) | (raw.yout1 << 2) | ((raw.xyzout2 >> 4) & 0x03)) - 0x20000;
    data.mag_z = ((raw.zout0 << 10) | (raw.zout1 << 2) | ((raw.xyzout2 >> 2) & 0x03)) - 0x20000;

    return ESP_OK;
}

void MMC::Verbose()
{
    printf("%7.2f %7.2f %7.2f\n", data.mag_x, data.mag_y, data.mag_z);
}

MMC5983MA_ConfigTypeDef MMC::getDefaultConfig()
{
    MMC5983MA_ConfigTypeDef config;
    config.bandwidth = BW_100HZ_8MS;
    config.continuousModeFreq = CMM_100HZ;
    config.periodicSetFreq = PRD_SET_1;
    return config;
}

esp_err_t MMC::SetConfig(MMC5983MA_ConfigTypeDef config)
{
    MMC5983MA_CtrlRegTypeDef ctrl;

    ctrl.reg_0 = 0b10000000;
    I2c->write(MMC5983MA_DEVICE_ID, MMC5983MA_INTERNAL_CTRL_0, &ctrl.reg_0, 0);

    vTaskDelay(10 / portTICK_PERIOD_MS);

    ctrl.reg_2 = config.periodicSetFreq << 4 | config.continuousModeFreq | MMC5983MA_CMM_EN;
    I2c->write(MMC5983MA_DEVICE_ID, MMC5983MA_INTERNAL_CTRL_2, &ctrl.reg_2, 0);

    return ESP_OK;
}
