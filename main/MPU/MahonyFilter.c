#include <math.h>
#include "MahonyFilter.h"
#include <stdio.h>


void MahonyFilter_Init2(MahonyFilter* filter, float kp, float ki) {
    filter->twoKp = kp * 2.0f;
    filter->twoKi = ki * 2.0f;
    filter->q0 = 1.0f;
    filter->q1 = 0.0f;
    filter->q2 = 0.0f;
    filter->q3 = 0.0f;
    filter->integralFBx = 0.0f;
    filter->integralFBy = 0.0f;
    filter->integralFBz = 0.0f;
}

float invSqrt(float x) {
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}


void MahonyFilter_Update(MahonyFilter* filter, float gx, float gy, float gz, float ax, float ay, float az, float dt) {
    float recipNorm;
    float halfvx, halfvy, halfvz;
    float halfex, halfey, halfez;
    float qa, qb, qc;

    // Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalization)
    if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {
        // Normalize accelerometer measurement
        recipNorm = invSqrt(ax * ax + ay * ay + az * az);
        ax *= recipNorm;
        ay *= recipNorm;
        az *= recipNorm;

        // Estimated direction of gravity
        halfvx = filter->q1 * filter->q3 - filter->q0 * filter->q2;
        halfvy = filter->q0 * filter->q1 + filter->q2 * filter->q3;
        halfvz = filter->q0 * filter->q0 - 0.5f + filter->q3 * filter->q3;

        // Error is sum of cross product between estimated and measured direction of gravity
        halfex = (ay * halfvz - az * halfvy);
        halfey = (az * halfvx - ax * halfvz);
        halfez = (ax * halfvy - ay * halfvx);

        // Compute and apply integral feedback if enabled
        if(filter->twoKi > 0.0f) {
            filter->integralFBx += filter->twoKi * halfex * dt; // integral error scaled by Ki
            filter->integralFBy += filter->twoKi * halfey * dt;
            filter->integralFBz += filter->twoKi * halfez * dt;
            gx += filter->integralFBx; // apply integral feedback
            gy += filter->integralFBy;
            gz += filter->integralFBz;
        }
        else {
            filter->integralFBx = 0.0f; // prevent integral windup
            filter->integralFBy = 0.0f;
            filter->integralFBz = 0.0f;
        }

        // Apply proportional feedback
        gx += filter->twoKp * halfex;
        gy += filter->twoKp * halfey;
        gz += filter->twoKp * halfez;
    }
    
    // Integrate rate of change of quaternion
    gx *= (0.5f * dt); // pre-multiply common factors
    gy *= (0.5f * dt);
    gz *= (0.5f * dt);
    qa = filter->q0;
    qb = filter->q1;
    qc = filter->q2;

    filter->q0 += (-qb * gx - qc * gy - filter->q3 * gz);
    filter->q1 += (qa * gx + qc * gz - filter->q3 * gy);
    filter->q2 += (qa * gy - qb * gz + filter->q3 * gx);
    filter->q3 += (qa * gz + qb * gy - qc * gx); 

    // Normalize quaternion
    recipNorm = invSqrt(filter->q0 * filter->q0 + filter->q1 * filter->q1 + filter->q2 * filter->q2 + filter->q3 * filter->q3);
    filter->q0 *= recipNorm;
    filter->q1 *= recipNorm;
    filter->q2 *= recipNorm;
    filter->q3 *= recipNorm;
}



// Function to get the quaternion values
void MahonyFilter_GetQuaternion(const MahonyFilter* filter, float *w, float *x, float *y, float *z) {
    *w = filter->q0;
    *x = filter->q1;
    *y = filter->q2;
    *z = filter->q3;
}


float MahonyFilter_getRoll(MahonyFilter* filter) {
    return atan2f(filter->q0 * filter->q1 + filter->q2 * filter->q3, 0.5f - filter->q1 * filter->q1 - filter->q2 * filter->q2);
}

float MahonyFilter_getPitch(MahonyFilter* filter) {
    return asinf(-2.0f * (filter->q1 * filter->q3 - filter->q0 * filter->q2));
}

float MahonyFilter_getYaw(MahonyFilter* filter) {
    return atan2f(filter->q1 * filter->q2 + filter->q0 * filter->q3, 0.5f - filter->q2 * filter->q2 - filter->q3 * filter->q3);
}

// void body_to_world(float body[3], float world[3], MahonyFilter* filter) {
//     // Compute the rotation matrix from the quaternion
//     float R[3][3] = {
//         {1 - 2*filter->q2*filter->q2 - 2*filter->q3*filter->q3, 2*filter->q1*filter->q2 - 2*filter->q0*filter->q3, 2*filter->q1*filter->q3 + 2*filter->q0*filter->q2},
//         {2*filter->q1*filter->q2 + 2*filter->q0*filter->q3, 1 - 2*filter->q1*filter->q1 - 2*filter->q3*filter->q3, 2*filter->q2*filter->q3 - 2*filter->q0*filter->q1},
//         {2*filter->q1*filter->q3 - 2*filter->q0*filter->q2, 2*filter->q2*filter->q3 + 2*filter->q0*filter->q1, 1 - 2*filter->q1*filter->q1 - 2*filter->q2*filter->q2}
//     };

//     // Multiply the body vector by the rotation matrix to get the world vector
//     world[0] = R[0][0]*body[0] + R[0][1]*body[1] + R[0][2]*body[2];
//     world[1] = R[1][0]*body[0] + R[1][1]*body[1] + R[1][2]*body[2];
//     world[2] = R[2][0]*body[0] + R[2][1]*body[1] + R[2][2]*body[2];
// }



void lowpass_filter(float input[3], FilterData *data) {
    // Define the alpha parameter for the filter
    float alpha = 0.95; // Adjust this value based on your needs

    // Apply the low-pass filter
    for (int i = 0; i < 3; i++) {
        input[i] = alpha * input[i] + (1 - alpha) * data->prev_output[i];

        // Update the previous input and output values
        data->prev_input[i] = input[i];
        data->prev_output[i] = input[i];
    }
}

void highpass_filter(float input[3], FilterData *data) {
    // Define the alpha parameter for the filter
    float alpha = 0.95; // Adjust this value based on your needs

    // Apply the high-pass filter
    for (int i = 0; i < 3; i++) {
        input[i] = alpha * data->prev_output[i] + alpha * (input[i] - data->prev_input[i]);

        // Update the previous input and output values
        data->prev_input[i] = input[i];
        data->prev_output[i] = input[i];
    }
}