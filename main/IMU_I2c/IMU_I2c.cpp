#include "IMU_I2c.hpp"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

// definitions for IMU_I2c class

static const char *TAG = "IMU_I2C";

esp_err_t IMU_I2C::init(void)
{

    if (esp_err_t ret = i2c_param_config(I2C_MASTER_NUM, &conf); ret != ESP_OK)
        return ret;

    return i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

esp_err_t IMU_I2C::scan(void)
{
    printf("\nScanning I2C bus...\n");
    uint8_t error, address;
    int devices_found = 0;
    for (address = 1; address < 127; address++)
    {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, 1 /* expect ack */);
        i2c_master_stop(cmd);

        error = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 10 / portTICK_PERIOD_MS);
        i2c_cmd_link_delete(cmd);

        if (error == ESP_OK)
        {
            ESP_LOGI(TAG, "I2C device found at address 0x%02x\n", address);
            devices_found++;
        }
        else if (error == ESP_ERR_TIMEOUT)
        {
            ESP_LOGE(TAG, "I2C bus is busy or device not responding at 0x%02x\n", address);
        }
    }

    if (devices_found == 0)
        ESP_LOGE(TAG, "No I2C devices found\n");

    return ESP_OK;
}

esp_err_t IMU_I2C::read(uint8_t dev_address, uint8_t reg_address, uint8_t *data_rd, size_t size)
{
    if (size == 0)
    {
        return ESP_OK;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_address << 1) | I2C_MASTER_WRITE, 1 /* expect ack */);
    i2c_master_write_byte(cmd, reg_address, 1 /* expect ack */);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_address << 1) | I2C_MASTER_READ, 1 /* expect ack */);

    if (size > 1)
    {
        i2c_master_read(cmd, data_rd, size - 1, I2C_MASTER_ACK);
    }
    i2c_master_read_byte(cmd, data_rd + size - 1, I2C_MASTER_NACK);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}


esp_err_t IMU_I2C::write(uint8_t dev_address, uint8_t reg_address, uint8_t *data_wr, size_t size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_address << 1) | I2C_MASTER_WRITE, 1 /* expect ack */);
    i2c_master_write_byte(cmd, reg_address, 1 /* expect ack */);
    i2c_master_write(cmd, data_wr, size, 1 /* expect ack */);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}