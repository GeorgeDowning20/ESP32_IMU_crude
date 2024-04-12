#pragma once

#define I2C_MASTER_NUM I2C_NUM_0  // default I2C port is 0
#define I2C_MASTER_SDA_IO 21      // default SDA pin is 21
#define I2C_MASTER_SCL_IO 22      // default SCL pin is 22
#define I2C_MASTER_FREQ_HZ 115200 // default frequency is 100kHz
#define I2C_MASTER_TX_BUF_DISABLE 0
#define I2C_MASTER_RX_BUF_DISABLE 0

#define MPU_6050_ADDR 0x68

#include "driver/i2c.h"
#include "esp_log.h"


class IMU_I2C
{
public:


    i2c_config_t conf;
    i2c_port_t i2c_num;

    IMU_I2C()
    {
        conf.mode = I2C_MODE_MASTER;
        conf.sda_io_num = I2C_MASTER_SDA_IO;
        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
        conf.scl_io_num = I2C_MASTER_SCL_IO;
        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
        conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
        conf.clk_flags = 0;

        init();
    }

    IMU_I2C(i2c_config_t conf, i2c_port_t i2c_num) : conf(conf), i2c_num(i2c_num)
    {
        init();
    }

    esp_err_t read(uint8_t dev_address, uint8_t reg_address, uint8_t *data_rd, size_t size);
    esp_err_t write(uint8_t dev_address, uint8_t reg_address, uint8_t *data_wr, size_t size);

    esp_err_t scan(void);

// private:
    // esp_err_t init(i2c_config_t conf, i2c_port_t i2c_num);
    esp_err_t init(void);
};
