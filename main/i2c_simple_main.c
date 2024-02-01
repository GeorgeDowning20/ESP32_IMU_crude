// main.c

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "BT.h"
#include "freertos/task.h"
#include "MPU/timer_module.h" // Include the header for the timer module
#include "MPU/MPU6500.h"
#include "MPU/i2c.h"
#include "MPU/registers.h"
#include "MPU/i2c_config.h"
#include "MPU/MahonyFilter.h"
#include <sys/time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "MPU/Madgwick.h"

mpu6050_data_t data;
MahonyFilter mahony;
MahonyFilter mahony2;

// double get_tic() {
//     return (double)timer_gettime() / 1000000.0;
// }

// void app_main(void)
// {
//      i2c_master_init();
//      MahonyFilter_Init(&mahony, 1);
//     // timer_setup();  // Setup the timer

//     // setup i2c

//     float time_minus_1 = -0.1;
//     float time = 0;
//     float dt = 1;
//     while (1)
//     {
//         time = get_tic();
//         dt = time - time_minus_1;
//         time_minus_1 = time;

//         read_mpu6050_data(&data);

//         // printf("accel_x: %d\t", data.accel_x);
//         // printf("accel_y: %d\t", data.accel_y);
//         // printf("accel_z: %d\t", data.accel_z);

//         // printf(" %d\t", data.gyro_x);
//         // printf(" %d\t", data.gyro_y);
//         // printf(" %d\n", data.gyro_z);

//         //   printf("Counter value: %llu\n", counter);
// //    readMPU();

//         MahonyFilter_Update(&mahony, data.gyro_x, data.gyro_y, data.gyro_z, data.accel_x, data.accel_y, data.accel_z,dt);

//         float roll = MahonyFilter_getRoll(&mahony);
//         float pitch = MahonyFilter_getPitch(&mahony);
//         float yaw = MahonyFilter_getYaw(&mahony);

//         printf("Roll: %f\t", roll);
//         printf("Pitch: %f\t", pitch);
//         printf("Yaw: %f\n", yaw);
//         printf("dt: %f\n", dt);

//         // delay 100 ms

//         vTaskDelay(100 / portTICK_PERIOD_MS);

//     }
// }
float accel[3];
float vel[3];
float pos[3];
float prev_accel[3], prev_vel[3];
// Define the high-pass filter parameters
float alpha = 0.8; // This value is between 0 and 1, adjust based on your needs

// Initialize the filtered velocity and the previous raw and filtered velocities
float filtered_vel[3] = {0, 0, 0};
float prev_raw_vel[3] = {0, 0, 0};
float prev_filtered_vel[3] = {0, 0, 0};

FilterData acc_lpf;
FilterData acc_hpf;
FilterData vel_hpf;
FilterData pos_hpf;

    float roll, pitch, yaw;


void control_loop_task(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(10); // 10 ms for 100 Hz

    // Initialise the xLastWakeTime variable with the current time
    xLastWakeTime = xTaskGetTickCount();


    while (1)
    {

        float dt = 0.01;
        read_mpu6050_data(&data);

        imu_filter(data.accel_x_g, data.accel_y_g, data.accel_z_g, data.gyro_x_dps, data.gyro_y_dps, data.gyro_z_dps);

        eulerAngles(q_est, &roll, &pitch, &yaw);

        // MahonyFilter_Update(&mahony, data.gyro_x_dps,
                            // data.gyro_y_dps, data.gyro_z_dps, data.accel_x_g,
                            // data.accel_y_g, data.accel_z_g, dt);
        // body_to_world((float[3]){data.accel_x_g, data.accel_y_g, data.accel_z_g}, accel, &mahony);

        // // Apply the high-pass filter to the acceleration
        // lowpass_filter(accel, &acc_lpf);
        // highpass_filter(accel, &acc_hpf);

        // vel[0] += 0.5f * (accel[0] + prev_accel[0]) * dt;
        // vel[1] += 0.5f * (accel[1] + prev_accel[1]) * dt;
        // vel[2] += 0.5f * ((accel[2] - 1) + (prev_accel[2] - 1)) * dt;

        // highpass_filter(vel, &vel_hpf);

        // // Update position using trapezium rule
        // pos[0] += 0.5f * (vel[0] + prev_vel[0]) * dt;
        // pos[1] += 0.5f * (vel[1] + prev_vel[1]) * dt;
        // pos[2] += 0.5f * (vel[2] + prev_vel[2]) * dt;

        // highpass_filter(pos, &pos_hpf);

        // // Update previous acceleration and velocity for the next iteration
        // prev_accel[0] = accel[0];
        // prev_accel[1] = accel[1];
        // prev_accel[2] = accel[2];
        // prev_vel[0] = vel[0];
        // prev_vel[1] = vel[1];
        // prev_vel[2] = vel[2];

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void second_task(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(100); // 10Hz = 100ms

    // Initialize the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    while (1)
    {

        // printf("%f\t, %f\t", accel[0], accel[1]);
        // printf("%f\t, %f\t", vel[0], vel[1]);
        // printf("%f\t, %f\n", pos[0], pos[1]);

        printf("Roll: %f\t", roll);
        printf("Pitch: %f\t", pitch);
        printf("Yaw: %f\n", yaw);

        // Do something here...
        // float roll = MahonyFilter_getRoll(&mahony);
        // float pitch = MahonyFilter_getPitch(&mahony);
        // float yaw = MahonyFilter_getYaw(&mahony);

        // printf("%f\t", roll*180/M_PI);
        // printf("%f\t", pitch*180/M_PI);
        // printf("%f\t", yaw*180/M_PI);

        // float roll2 = MahonyFilter_getRoll(&mahony2);
        // float pitch2 = MahonyFilter_getPitch(&mahony2);
        // float yaw2 = MahonyFilter_getYaw(&mahony2);

        // printf("%f\t", roll2*180/M_PI);
        // printf("%f\t", pitch2*180/M_PI);
        // printf("%f\n", yaw2*180/M_PI);

        // printf("gyro_x: %f\t", data.gyro_x_dps);
        // printf("gyro_y: %f\t", data.gyro_y_dps);
        // printf("gyro_z: %f\t", data.gyro_z_dps);

        // printf("accel_x: %f\t", data.accel_x_g);
        // printf("accel_y: %f\t", data.accel_y_g);
        // printf("accel_z: %f\n", data.accel_z_g);

        // printf(" Q1: %f\t", mahony.q0);
        // printf(" Q2: %f\t", mahony.q1);
        // printf(" Q3: %f\t", mahony.q2);
        // printf(" Q4: %f\n", mahony.q3);
        // Wait for the next cycle.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void app_main(void)
{

    i2c_master_init();
    MahonyFilter_Init2(&mahony, 0.08, 0.001);
    calibrate_mpu6050();

    xTaskCreate(&control_loop_task, "Control Loop Task", 2048, NULL, 1, NULL);
    xTaskCreate(&second_task, "Second Task", 2048, NULL, 1, NULL);
}
