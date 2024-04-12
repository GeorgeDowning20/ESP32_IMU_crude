#pragma once
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_err.h"

typedef struct
{
    double x;
    double y;
    double z;
} bias_t;

typedef struct
{
    double x[3];
    double y[3];
    double z[3];
} rotation_t;

typedef struct
{
    double x;
    double y;
    double z;
} scale_t;


typedef struct
{
    bias_t bias;
    rotation_t rot;
    scale_t scale;
} vec_offsets_t;

typedef struct
{
    bias_t bias;
} rate_offsets_t;

class Offsets
{
private:
    /* data */
public:
    vec_offsets_t accel;
    vec_offsets_t mag;
    rate_offsets_t gyro;

    esp_err_t save();
    esp_err_t load();

    void print();
};


