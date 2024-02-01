// main.c

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "MPU/timer_module.h" // Include the header for the timer module
#include "MPU/MPU6500.h"
#include "MPU/i2c.h"
#include "MPU/registers.h"
#include "MPU/i2c_config.h"
// #include "MPU/MahonyFilter.h"
#include <sys/time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "MPU/Madgwick.h"

#include "BT/esp_ibeacon_api.h"
#include "BT/Beacon.h"

#include "genericFlt.h"

#include "KalmanF/state.h"
#include "KalmanF/1d_KF.h"

mpu6050_data_t data;

float roll, pitch, yaw;

float accel[3], vel[3], pos[3];
float accelhpf[3], velhpf[3], poshpf[3];
float accellpf[3], vellpf[3], poslpf[3];
float accelbpf[3], velbpf[3], posbpf[3];

float prev_accel[2] = {0, 0};
float prev_vel[2] = {0, 0};

    float velthresh[2];

Position_t position = {0,-10};

// void control_loop_task(void *pvParameters)
// {
//     TickType_t xLastWakeTime;
//     const TickType_t xFrequency = pdMS_TO_TICKS(10); // 10 ms for 100 Hz
//     xLastWakeTime = xTaskGetTickCount();


//     while (1)
//     {

//         float dt = 0.01;
//         read_mpu6050_data(&data);

//         imu_filter(data.accel_x_g, data.accel_y_g, data.accel_z_g, data.gyro_x_dps, data.gyro_y_dps, data.gyro_z_dps);
//         eulerAngles(q_est, &roll, &pitch, &yaw);

//         body_to_world((float[3]){data.accel_x_g, data.accel_y_g, data.accel_z_g}, accel, q_est);

//         // accel[0] = bpf(100, 0.001, 100, accel[0], &accelbpf[0])*9.8;
//         // accel[1] = bpf(100, 0.001, 100, accel[1], &accelbpf[1])*9.8;

//         accel[0] = 9.8*accel[0];
//         accel[1] = 9.8*accel[1];

//     //    vel[0] += 0.5 * (accel[0] + prev_accel[0]) * dt;
//     //    vel[1] += 0.5 * (accel[1] + prev_accel[1]) * dt;
//     vel[0] += accel[0] * dt;
//     vel[1] += accel[1] * dt;

//     //    float stop0 = 0.1/(1+accel[0]);
//         // float stop1 = 0.1/(1+accel[1]);

//         float stop0 = 0.1;
//         float stop1 = 0.1;

//         // vel[0] = bpf(1000, stop0, 100, vel[0], &velbpf[0]);
//         // vel[1] = bpf(1000, stop1, 100, vel[1], &velbpf[1]);

//         vel[0] = hpf(0.5, 100, vel[0], &velhpf[0]);
//         vel[1] = hpf(0.5, 100, vel[1], &velhpf[1]);

//     prev_accel[0] = accel[0];
//     prev_accel[1] = accel[1];


//     velthresh[0] = threshold(vel[0], 0.002);
//     velthresh[1] = threshold(vel[1], 0.002);

//      prev_vel[0] = velthresh[0];
//     prev_vel[1] = velthresh[1];



//    pos[0] += 0.5 * (velthresh[0] + prev_vel[0]) * dt;
//     pos[1] += 0.5 * (velthresh[1] + prev_vel[1]) * dt;

//     // pos[0] = hpf(0.01, 100, pos[0], &poshpf[0]);
//     // pos[1] = hpf(0.01, 100, pos[1], &poshpf[1]);
//         update_beacon(&b1);
//         update_beacon(&b2);

//         // printf("%f\t, %f\n", b1.distance, b2.distance);

        
//         position.x += 0.5 * (velthresh[0] + prev_vel[0]) * dt * 400;//cm/s
//         position.y += 0.5 * (velthresh[1] + prev_vel[1]) * dt * 400;//cm/s

//         // position = update
        
//         // e_pos(position, 0.1);    
        
//         vTaskDelayUntil(&xLastWakeTime, xFrequency);

      
//     }
// }

State1d_f state = {0, 0, 0, 1, 1, 1};

void control_loop_task(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(10); // 10 ms for 100 Hz
    xLastWakeTime = xTaskGetTickCount();


    while (1)
    {

        float dt = 0.01;
        read_mpu6050_data(&data);

        imu_filter(data.accel_x_g, data.accel_y_g, data.accel_z_g, data.gyro_x_dps, data.gyro_y_dps, data.gyro_z_dps);
        eulerAngles(q_est, &roll, &pitch, &yaw);

        body_to_world((float[3]){data.accel_x_g, data.accel_y_g, data.accel_z_g}, accel, q_est);

        accel[0] = 9.8*accel[0]*100;
        accel[1] = 9.8*accel[1*100];

        update_beacon(&b1);
        update_beacon(&b2);

        Beacon1d_t B1 = {40-b1.distance, b1.variance};
        Beacon1d_t B2 = {-40+b2.distance, b2.variance};

        State1d_f predict = Predict(state, accel[0], dt, 0.1);
        state = Update(predict, state, dt, B1, B2);

        vTaskDelayUntil(&xLastWakeTime, xFrequency);

      
    }
}



void second_task(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(50); // 10Hz = 100ms

    // Initialize the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    while (1)
    {

        // printf("Roll: %f\t", roll);
        // printf("Pitch: %f\t", pitch);
        // printf("Yaw: %f\n", yaw);

        // printf("%f\t, %f\n", accel[0], accel[1]);

        // printf("%f\t, %f\n", vel[0]*100, vel[1]*100);

        // printf("%f\t, %f\n", pos[0]*100, pos[1]*100);

        // accel,vel and pos
        // printf("%f\t, %f\t, %f\t, %f\t, %f\t, %f\n", accel[0], accel[1], vel[0], vel[1], pos[0], pos[1]);
        // printf(">a:%f\n >b:%f\n >c:%f\n", accel[0], velthresh[0], pos[0]);
        // printf("%f\t, %f\t", beacon1+beacon2, beacon2);
        // printf(">a:%f\n",accel[0]);
        // printf(">b:%f\n",velthresh[0]);
        // printf(">c:%f\n",pos[0]);

        // printf("%f\t, %f\t", vel[0], vel[1

        // printf("%f\t, %f\t", b1.recived_power_db, b2.recived_power_db);

        // printf("%f\t, %f\n", 40-b1.distance, -40+b2.distance);


         
        printf("%f\t, %f\n", state.pos, 0.f);
        // printf("%f\t, %f\n", position.x, position.y);

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void app_main(void)
{
    ble_ibeacon_init();

    i2c_master_init();
    calibrate_mpu6050();

    xTaskCreate(&control_loop_task, "Control Loop Task", 2048, NULL, 1, NULL);
    xTaskCreate(&second_task, "Second Task", 2048, NULL, 1, NULL);
}
