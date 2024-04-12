#pragma once


#include "../IMU.h"
// #include "magcal.h"
#include "magcalibrate/magcalibrate.h"
#include "magcalibrate/magcalibrate_terminate.h"
#include "magcalibrate/rt_nonfinite.h"
#include "Offsets.h"

typedef struct
{
    double accX;
    double accY;
    double accZ;

    double magX;
    double magY;
    double magZ;
} accel_mag_frame_t;

class CalSesnsor
{
public:
    CalSesnsor(IMU *imu);
    ~CalSesnsor() = default;

    void run();
    void CalibrateAccel();
    void CalibrateMag();

    Offsets offsets;

    IMU *imu;

private:
    double accX[36];
    double accY[36];
    double accZ[36];

    double magX[36];
    double magY[36];
    double magZ[36];

    accel_mag_frame_t SampleVectors();
};
