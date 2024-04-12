#pragma once

#include "CalSensor.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"

CalSesnsor::CalSesnsor(IMU *imu)
{
    this->imu = imu;
}

void CalSesnsor::run()
{
    printf("Calibrating Sensor\n");
    printf("36 measurements will be taken\n");
    printf("Please keep the sensor still\n");
    printf("move to a new position and press enter to conintue\n");
    uint8_t c;

    for (int i = 0; i < 36; i++)
    {
        printf("Sample %d press enter to continue\n", i);

        // esp_task_wdt_delete(NULL);
        while (getchar() != '\n')
        {
            c++;
            vTaskDelay(pdMS_TO_TICKS(10));
        };
        // esp_task_wdt_add(NULL);

        printf("sampling\n");
        accel_mag_frame_t meas = SampleVectors();

        accX[i] = meas.accX;
        accY[i] = meas.accY;
        accZ[i] = meas.accZ;

        magX[i] = meas.magX;
        magY[i] = meas.magY;
        magZ[i] = meas.magZ;
    }

    // printf("data collected\n");
}

accel_mag_frame_t CalSesnsor::SampleVectors()
{
    accel_mag_frame_t meas;

    const int samples = 50;
    meas.accX = 0;
    meas.accY = 0;
    meas.accZ = 0;

    meas.magX = 0;
    meas.magY = 0;
    meas.magZ = 0;

    for (int i = 0; i < samples; i++)
    {
        imu->readDevices();
        meas.accX += imu->GetAccel().g().x;
        meas.accY += imu->GetAccel().g().y;
        meas.accZ += imu->GetAccel().g().z;

        meas.magX += imu->GetMag().Gauss().x;
        meas.magY += imu->GetMag().Gauss().y;
        meas.magZ += imu->GetMag().Gauss().z;

        // delay 10ms
        vTaskDelay(pdMS_TO_TICKS(10));
        if (i % 30 == 0)
            printf("%d \t \r", i / 3);
    }

    meas.accX /= samples;
    meas.accY /= samples;
    meas.accZ /= samples;

    meas.magX /= samples;
    meas.magY /= samples;
    meas.magZ /= samples;

    printf("Accel: %7.2f %7.2f %7.2f\t", meas.accX, meas.accY, meas.accZ);
    printf("Mag: %7.2f %7.2f %7.2f\n", meas.magX, meas.magY, meas.magZ);

    return meas;
}

void CalSesnsor::CalibrateAccel()
{
    double A[9];
    double b[3];
    double expmfs;

    magcalibrate(accX, accY, accZ, A, b, &expmfs);

    printf("A: %f %f %f\n", A[0], A[1], A[2]);
    printf("A: %f %f %f\n", A[3], A[4], A[5]);
    printf("A: %f %f %f\n", A[6], A[7], A[8]);
    printf("b: %f %f %f\n", b[0], b[1], b[2]);
    printf("expmfs: %f\n", expmfs);

    offsets.accel.bias.x = b[0];
    offsets.accel.bias.y = b[1];
    offsets.accel.bias.z = b[2];

    offsets.accel.rot.x[0] = A[0];
    offsets.accel.rot.x[1] = A[1];
    offsets.accel.rot.x[2] = A[2];

    offsets.accel.rot.y[0] = A[3];
    offsets.accel.rot.y[1] = A[4];
    offsets.accel.rot.y[2] = A[5];

    offsets.accel.rot.z[0] = A[6];
    offsets.accel.rot.z[1] = A[7];
    offsets.accel.rot.z[2] = A[8];

    offsets.accel.scale.x = 1.0 / expmfs;
    offsets.accel.scale.y = 1.0 / expmfs;
    offsets.accel.scale.z = 1.0 / expmfs;

    offsets.save();

    magcalibrate_terminate();
}

void CalSesnsor::CalibrateMag()
{
    double A[9];
    double b[3];
    double expmfs;

    magcalibrate(magX, magY, magZ, A, b, &expmfs);

    printf("A: %f %f %f\n", A[0], A[1], A[2]);
    printf("A: %f %f %f\n", A[3], A[4], A[5]);
    printf("A: %f %f %f\n", A[6], A[7], A[8]);
    printf("b: %f %f %f\n", b[0], b[1], b[2]);
    printf("expmfs: %f\n", expmfs);

    offsets.mag.bias.x = b[0];
    offsets.mag.bias.y = b[1];
    offsets.mag.bias.z = b[2];

    offsets.mag.rot.x[0] = A[0];
    offsets.mag.rot.x[1] = A[1];
    offsets.mag.rot.x[2] = A[2];

    offsets.mag.rot.y[0] = A[3];
    offsets.mag.rot.y[1] = A[4];
    offsets.mag.rot.y[2] = A[5];

    offsets.mag.rot.z[0] = A[6];
    offsets.mag.rot.z[1] = A[7];
    offsets.mag.rot.z[2] = A[8];

    // offsets.mag.scale.x = 1.0 / expmfs;
    // offsets.mag.scale.y = 1.0 / expmfs;
    // offsets.mag.scale.z = 1.0 / expmfs;

    offsets.save();

    magcalibrate_terminate();
}
