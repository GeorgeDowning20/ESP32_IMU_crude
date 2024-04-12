#include "IMU.h"
#include <math.h>


void IMU::init(IMU_I2C *i2c, MMC *mmc, ISM *ism)
{
    this->I2c = i2c;
    this->mmc = mmc;
    this->ism = ism;

    mmc->init(i2c);
    ism->init(i2c);

    SetSensitivities();

     offsets.load();
}

void IMU::init()
{
    static IMU_I2C i2c;
    static MMC mmc;
    static ISM ism;

    this->I2c = &i2c;
    this->mmc = &mmc;
    this->ism = &ism;

    mmc.init(&i2c);
    ism.init(&i2c);

    SetSensitivities();

     offsets.load();
}

void IMU::reloadOffsets()
{
    offsets.load();
    offsets.print();
}


esp_err_t IMU::readDevices()
{
    if (mmc->read() != ESP_OK)
        return ESP_FAIL;
    if (ism->read() != ESP_OK)
        return ESP_FAIL;

    return ESP_OK;
}

esp_err_t IMU::VerboseDeviceRaw()
{
    printf("Mag: %7.2f %7.2f %7.2f\t", mmc->data.mag_x, mmc->data.mag_y, mmc->data.mag_z);
    printf("Gyro: %7.2f %7.2f %7.2f\t", ism->data.gyro_x, ism->data.gyro_y, ism->data.gyro_z);
    printf("Accel: %7.2f %7.2f %7.2f\n", ism->data.accel_x, ism->data.accel_y, ism->data.accel_z);

    return ESP_OK;
}

esp_err_t IMU::Verbose()
{
    Vector3f mag = GetMag().Gauss();
    Vector3f gyro = GetGyro().dps();
    Vector3f accel = GetAccel().g();

    printf("Mag: %7.2f %7.2f %7.2f\t", mag.x, mag.y, mag.z);
    printf("Gyro: %7.2f %7.2f %7.2f\t", gyro.x, gyro.y, gyro.z);
    printf("Accel: %7.2f %7.2f %7.2f\t", accel.x, accel.y, accel.z);
    
    float mag_norm = sqrt(mag.x * mag.x + mag.y * mag.y + mag.z * mag.z);
    float Accel_norm = sqrt(accel.x * accel.x + accel.y * accel.y + accel.z * accel.z);

    printf("Mag norm: %f\t Accel norm: %f\n", mag_norm, Accel_norm);

    return ESP_OK;
}

Vector3f IMU::GetMag()
{
    Vector3f mag;
    mag.x = mmc->data.mag_x * MagSensitivity;    // Gauss
    mag.y = mmc->data.mag_y * MagSensitivity;    
    mag.z = mmc->data.mag_z * MagSensitivity;

    return mag;
}

Vector3f IMU::GetGyro()
{
    Vector3f gyro;
    gyro.x = ism->data.gyro_x * GyroSensitivity;
    gyro.y = ism->data.gyro_y * GyroSensitivity;
    gyro.z = ism->data.gyro_z * GyroSensitivity;

    return gyro;
}

Vector3f IMU::GetAccel()
{
    Vector3f accel;
    accel.x = ism->data.accel_x * AccelSensitivity;
    accel.y = ism->data.accel_y * AccelSensitivity;
    accel.z = ism->data.accel_z * AccelSensitivity;

    return accel;
}

void IMU::applyOffsets()
{

    accel = GetAccel().g();
    printf("Accel:%7.2f %7.2f %7.2f\t", accel.x, accel.y, accel.z);
    double magnetude = sqrt(accel.x * accel.x + accel.y * accel.y + accel.z * accel.z);
    double s_60s_error = 0.5*(1.0-magnetude)*3600;

    printf("Magnetude: %f\t", magnetude);
    printf("60s error: %f\t", s_60s_error);

    accel.x -= offsets.accel.bias.x;
    accel.y -= offsets.accel.bias.y;
    accel.z -= offsets.accel.bias.z;

    accel.x = accel.x*offsets.accel.rot.x[0] + accel.y*offsets.accel.rot.x[1] + accel.z*offsets.accel.rot.x[2];
    accel.y = accel.x*offsets.accel.rot.y[0] + accel.y*offsets.accel.rot.y[1] + accel.z*offsets.accel.rot.y[2];
    accel.z = accel.x*offsets.accel.rot.z[0] + accel.y*offsets.accel.rot.z[1] + accel.z*offsets.accel.rot.z[2];

    accel.x *= offsets.accel.scale.x;
    accel.y *= offsets.accel.scale.y;
    accel.z *= offsets.accel.scale.z;

    printf("Accel: %7.2f %7.2f %7.2f\t", accel.x, accel.y, accel.z);
    magnetude = sqrt(accel.x * accel.x + accel.y * accel.y + accel.z * accel.z);
    s_60s_error = 0.5*(1.0-magnetude)*3600;
    printf("Magnetude: %f\t", magnetude);
    printf("60s error: %f\n", s_60s_error);
}   

void IMU::SetSensitivities(void)
{
    MagSensitivity = (8.0 * 2) / 262144; // Gauss
    printf("MagSensitivity: %f\n", MagSensitivity);

    switch (ism->config.gyro_fs)
    {
    case ISM330DHCX_125dps:
        GyroSensitivity = ((125.0*4) / 0xffff) * degToRad; // rad/s
        break;
    case ISM330DHCX_250dps:
        GyroSensitivity = ((250.0*4) / 0xffff) * degToRad; // rad/s
        break;
    case ISM330DHCX_500dps:
        GyroSensitivity = ((500.0*4) / 0xffff) * degToRad; // rad/s
        break;
    case ISM330DHCX_1000dps:
        GyroSensitivity = ((1000.0*4) / 0xffff) * degToRad; // rad/s
        break;
    case ISM330DHCX_2000dps:
        GyroSensitivity = ((2000.0*4) / 0xffff) * degToRad; // rad/s
        break;
    case ISM330DHCX_4000dps:
        GyroSensitivity = ((4000.0*4) / 0xffff) * degToRad; // rad/s
        break;
    default:
        GyroSensitivity = ((250.0*4) / 0xffff) * degToRad; // rad/s
        break;
    }

    switch (ism->config.acc_fs)
    {
    case ISM330DHCX_2g:
        AccelSensitivity = ((2.0 * 2) / 0xffff) * AccelGravity; // m/s^2
        break;
    case ISM330DHCX_4g:
        AccelSensitivity = ((4.0 * 2) / 0xffff) * AccelGravity; // m/s^2
        break;
    case ISM330DHCX_8g:
        AccelSensitivity = ((8.0 * 2) / 0xffff) * AccelGravity; // m/s^2
        break;
    case ISM330DHCX_16g:
        AccelSensitivity = ((16.0 * 2) / 0xffff) * AccelGravity; // m/s^2
        break;
    default:
        AccelSensitivity = ((2.0 * 2) / 0xffff) * AccelGravity; // m/s^2
        break;
    }
}
