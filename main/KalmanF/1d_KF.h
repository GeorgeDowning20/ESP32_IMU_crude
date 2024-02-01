#pragma once

typedef struct state1d{
    float accel;
    float vel;
    float pos;

    float accel_var;
    float vel_var;
    float pos_var;
} State1d_f;

typedef struct Beacon_1d{
    float pos;
    float variance;
} Beacon1d_t;

typedef struct KalmanGain1d{
    float accel;
    float vel;
    float pos;
} KalmanGain1d_t;

State1d_f Predict(State1d_f state, float accel, float dt, float accel_var);
State1d_f Update(State1d_f state, State1d_f Old, float dt, Beacon1d_t beacon1, Beacon1d_t beacon2);