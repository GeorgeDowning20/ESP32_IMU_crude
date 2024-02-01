#include "Beacon.h"


float lim(float input)
{
    if (input > 0) return 0;
    else return input;
}

void update_beacon(beacon_t *b)
{
    b->distance = b->gain*lim(b->recived_power_db - b->Max_power_db);
    b->variance = b->distance * 10;
}