#pragma once


typedef struct beacon_s{
    float x;
    float y;
    float Max_power_db;
    float gain;
    float noise;    //cm

    float recived_power_db;
    float distance;
    float variance;
} beacon_t;

extern beacon_t b1, b2;


void update_beacon(beacon_t *b);
