#pragma once

#include "MMC/MMC.h"
#include "ISM/ISM.h"
#include "../../IMU_I2c/IMU_I2c.hpp"
#include "esp_err.h"

#define PI 3.14159265358979323846
#define AccelGravity 9.80665
#define GaussTonT 1e5
#define degToRad (PI / 180.0)
#define radToDeg (180.0 / PI)

class Vector3f
{
public:
    float x;
    float y;
    float z;

    Vector3f Gauss()
    {
        return *this;
    }

    Vector3f nTesla()
    {
        x *= GaussTonT;
        y *= GaussTonT;
        z *= GaussTonT;
        return *this;
    }

    Vector3f mps2()
    {
        return *this;
    }

    Vector3f g()
    {
        x /= AccelGravity;
        y /= AccelGravity;
        z /= AccelGravity;
        return *this;
    };

    Vector3f radps()
    {
        return *this;
    }

    Vector3f dps()
    {
        x *= radToDeg;
        y *= radToDeg;
        z *= radToDeg;
        return *this;
    }
};

class IMU
{
public:

    IMU(){};

    void init(IMU_I2C *i2c, MMC *mmc, ISM *ism);
    void init();

    esp_err_t readDevices();
    esp_err_t VerboseDeviceRaw();
    esp_err_t Verbose();

    Vector3f GetMag();
    Vector3f GetGyro();
    Vector3f GetAccel();

    void SetSensitivities(void);

    IMU_I2C *I2c;
    MMC *mmc;
    ISM *ism;

private:
    float MagSensitivity;
    float GyroSensitivity;
    float AccelSensitivity;
};