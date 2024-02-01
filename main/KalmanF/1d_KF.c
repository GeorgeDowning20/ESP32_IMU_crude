#include "1d_KF.h"

const float dt = 0.01;


State1d_f Predict(State1d_f state, float accel, float dt, float accel_var)
{
    State1d_f new_state;
    new_state.accel = accel;
    new_state.vel = state.vel + state.accel * dt;
    new_state.pos = state.pos + state.vel * dt + 0.5 * state.accel * dt * dt;

    new_state.accel_var = state.accel_var;
    new_state.vel_var = state.vel_var + accel_var * dt;
    new_state.pos_var = state.pos_var + state.vel_var * dt + 0.5 * accel_var * dt * dt;

    return new_state;
}

State1d_f Update(State1d_f state, State1d_f Old, float dt, Beacon1d_t beacon1, Beacon1d_t beacon2){
    
    // float kalman_gain = state.pos_var / (state.pos_var + beacon1.variance + beacon2.variance);
    float kalman_b1 = state.pos_var / (state.pos_var + beacon1.variance);
    float kalman_b2 = state.pos_var / (state.pos_var + beacon2.variance);

    State1d_f new_state = state;

    new_state.pos = state.pos + kalman_b1 * (beacon1.pos - state.pos)
                              + kalman_b2 * (beacon2.pos - state.pos);

    new_state.pos_var = (1 - kalman_b1 - kalman_b2) * state.pos_var;

    float vel = (state.pos - Old.pos)/dt;
    float vel_var = (state.pos_var + Old.pos_var)/dt;

    float velKalmanGain = state.vel_var / (state.vel_var + vel_var);

    new_state.vel = state.vel + velKalmanGain * (vel - state.vel);



    return new_state;
}