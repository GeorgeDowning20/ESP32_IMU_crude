#pragma once

typedef struct pos{
    float x;
    float y;
} Position_t;


typedef struct vector2{
    float x;
    float y;
} Vector_2f;

typedef struct state{
    Position_t pos;
    Vector_2f vel;
    Vector_2f acc;

    Position_t pos_cov;
    Vector_2f vel_cov;
    Vector_2f acc_cov;
} State_f;


Position_t update_pos(Position_t est, float k_gain);
