#pragma once

typedef struct {
    float q0, q1, q2, q3; // quaternion elements representing the estimated orientation
    float beta; // algorithm gain
    float integralError[3];
     float twoKp; // 2 * proportional gain (Kp)
    float twoKi; // 2 * integral gain (Ki)
     float integralFBx, integralFBy, integralFBz;
} MahonyFilter;

typedef struct {
    float prev_input[3];
    float prev_output[3];
} FilterData;


void MahonyFilter_Init(MahonyFilter* filter, float beta);
void MahonyFilter_Update(MahonyFilter* filter, float gx, float gy, float gz, float ax, float ay, float az, float dt);
float MahonyFilter_getRoll(MahonyFilter* filter);
float MahonyFilter_getPitch(MahonyFilter* filter);
float MahonyFilter_getYaw(MahonyFilter* filter);
void MahonyFilter_Init2(MahonyFilter* filter, float kp, float ki);
// void body_to_world(float body[3], float world[3], MahonyFilter* filter);
void highpass_filter(float input[3], FilterData *data);
void lowpass_filter(float input[3], FilterData *data);