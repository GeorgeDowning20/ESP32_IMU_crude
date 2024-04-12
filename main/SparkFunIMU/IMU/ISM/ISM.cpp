
#include "ISM.h"
#include "math.h"

// ISM::ISM()
// {
//     config = getDefaultConfig();
//     SetConfig();
//     return;
// }

// ISM::ISM(IMU_I2C &i2c)
//     : I2c(i2c)
// {
//     config = getDefaultConfig();
//     SetConfig();
//     return;
// }

esp_err_t ISM::init(IMU_I2C *i2c)
{
    I2c = i2c;
    config = getDefaultConfig();
    SetConfig();
    return ESP_OK;
}

ISM330DHCX_ConfigTypeDef ISM::getDefaultConfig()
{
    ISM330DHCX_ConfigTypeDef config;
    config.acc_odr = ISM330DHCX_XL_ODR_104Hz;
    config.acc_fs = ISM330DHCX_2g;

    config.gyro_odr = ISM330DHCX_GY_ODR_104Hz;
    config.gyro_fs = ISM330DHCX_500dps;

    config.fifo_mode = ISM330DHCX_BYPASS_MODE;
    config.fifo_threshold = 0;

    config.int1_config = 0;
    config.int2_config = 0;

    return config;
};

esp_err_t ISM::read()
{
    // printf("Gyro: %d \n", raw.OUT_TEMP_L);
    I2c->read(ISM330DHCX_ADDRESS, ISM330DHCX_OUT_TEMP_L, (uint8_t *)&raw, sizeof(ISM330DHCX_OutputDataTypeDef));
    data.temp = (float)((int16_t)(raw.OUT_TEMP_H << 8 | raw.OUT_TEMP_L)) / 16.0f + 25.0f;
    // data.temp = (float)((int16_t)(raw.OUT_TEMP_H << 8 | raw.OUT_TEMP_L));

    data.gyro_x = (float)((int16_t)(raw.OUTX_H_G << 8 | raw.OUTX_L_G));
    data.gyro_y = -(float)((int16_t)(raw.OUTY_H_G << 8 | raw.OUTY_L_G));
    data.gyro_z = -(float)((int16_t)(raw.OUTZ_H_G << 8 | raw.OUTZ_L_G));

    // I2c.read(ISM330DHCX_ADDRESS, ISM330DHCX_OUTX_L_A, (uint8_t*)&raw.OUTX_L_A, 2);

    data.accel_x = (float)((int16_t)(raw.OUTX_H_A << 8 | raw.OUTX_L_A));
    data.accel_y = -(float)((int16_t)(raw.OUTY_H_A << 8 | raw.OUTY_L_A));
    data.accel_z = -(float)((int16_t)(raw.OUTZ_H_A << 8 | raw.OUTZ_L_A));

    return ESP_OK;
};

void ISM::Verbose()
{
     printf("Accel: %7.2f %7.2f %7.2f \t Gyro: %7.2f %7.2f %7.2f \t Temp: %7.2f\t g: %f\n",
           data.accel_x, data.accel_y, data.accel_z,
           data.gyro_x, data.gyro_y, data.gyro_z,
           data.temp, (sqrt(data.accel_x * data.accel_x + data.accel_y * data.accel_y + data.accel_z * data.accel_z) / 16384));
}

esp_err_t ISM::WhoAmI()
{
    uint8_t sensor_data[1];
    I2c->read(ISM330DHCX_ADDRESS, ISM330DHCX_WHO_AM_I, sensor_data, 1);
    printf("WHO_AM_I: 0x%02x\n", sensor_data[0]);
    return ESP_OK;
}

esp_err_t ISM::SetConfig()
{
    uint8_t ctrl1_xl = (config.acc_odr << 4) | (config.acc_fs << 2);
    uint8_t ctrl2_g = (config.gyro_odr << 4) | (config.gyro_fs << 1);
    uint8_t ctrl3_c = 0x04; // BDU enable

    // printf("im here\n");

    I2c->write(ISM330DHCX_ADDRESS, ISM330DHCX_CTRL1_XL, &ctrl1_xl, 1);
    I2c->write(ISM330DHCX_ADDRESS, ISM330DHCX_CTRL2_G, &ctrl2_g, 1);
    I2c->write(ISM330DHCX_ADDRESS, ISM330DHCX_CTRL3_C, &ctrl3_c, 1);
    return ESP_OK;
}
