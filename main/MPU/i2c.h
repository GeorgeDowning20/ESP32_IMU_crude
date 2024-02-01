#pragma once
#include "driver/i2c.h"

esp_err_t i2c_master_init(void);
void Scan_i2c(void);
esp_err_t i2c_master_read_device(i2c_port_t i2c_num, uint8_t dev_address, uint8_t reg_address, uint8_t* data_rd, size_t size);
esp_err_t i2c_master_write_device(i2c_port_t i2c_num, uint8_t dev_address, uint8_t reg_address, uint8_t* data_wr, size_t size);