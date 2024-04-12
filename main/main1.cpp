#include "Util/test.h"
#include "IMU_I2c/IMU_I2c.hpp"
#include "SparkFunIMU/IMU/IMU.h"
#include <esp_types.h>
#include "SparkFunIMU/IMU/ISM/ISM.h"
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "SparkFunIMU/Orientation/Madgwick.h"

// #include "SparkFunIMU/IMU/Calabration/magcal.h"
#include "esp_task_wdt.h"
#include "SparkFunIMU/IMU/Calabration/CalSensor.h"

#define WHO_AM_I 0x6B

IMU imu;
Vector3f acc;
Vector3f gyro;
Vector3f mag;

void task1(void *pvParameter)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(10); // 10 ms for 100 Hz
    xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        imu.readDevices();
        acc = imu.GetAccel().g();
        gyro = imu.GetGyro().radps();
        mag = imu.GetMag().Gauss();

        imu_filter(acc.x, acc.y, acc.z, gyro.x, gyro.y, gyro.z);
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void task2(void *pvParameter)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(50); // 10 ms for 100 Hz
    xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        // imu.Verbose();

        float roll, pitch, yaw;
        eulerAngles(q_est, &roll, &pitch, &yaw);
        
        imu.applyOffsets();
        // printf("Roll: %f, Pitch: %f, Yaw: %f\n", roll, pitch, yaw);
        // printf("acc: %f %f %f\n", acc.x, acc.y, acc.z);
        vTaskDelayUntil(&xLastWakeTime, xFrequency); // 5Hz
    }
}

extern "C" void app_main()
{
    printf("Hello world espressif\n");
    // esp_task_wdt_delete(NULL);

    // Your long-running operation here

    // Re-enable the watchdog timer
    // esp_task_wdt_add(NULL);
    // esp_err_t err = esp_task_wdt_delete(xTaskGetCurrentTaskHandle());
    // if (err != ESP_OK) {
    //     printf("Task was not being monitored by the watchdog timer\n");
    // }

    // mainmagcal();

    imu.init();

    CalSesnsor cal(&imu);
    // cal.run();
    // cal.CalibrateAccel(); 
    cal.offsets.load();
    cal.offsets.print();

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    printf("end\n");

    // while (1)
    // {
    // };

    // imu.init();

     xTaskCreate(&task1, "Task 1", 2048, NULL, 1, NULL);
     xTaskCreate(&task2, "Task 2", 2048, NULL, 1, NULL);
}