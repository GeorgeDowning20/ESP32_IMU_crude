#include "../BT/Beacon.h"
#include  "state.h"
#include "math.h"
#include "stdio.h"

// fast inverse square-root
float invSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int *)&x; // store floating-point bits in integer
    i = 0x5f3759df - (i >> 1); // initial guess for Newton's method
    x = *(float *)&i; // convert new bits into float
    x = x * (1.5f - xhalf * x * x); // One round of Newton's method
    return x;
}


Vector_2f Beacon_innovation(beacon_t *b, Position_t est)
{
    Vector_2f inovation;
    inovation.x = b->x - est.x;
    inovation.y = b->y - est.y;

    // error is the difference between magnitude of the mesured (b->distance) and the estimated distance (sqrt(x^2 + y^2))

    float distance = sqrt(inovation.x * inovation.x + inovation.y * inovation.y);
    float error = b->distance - distance;

    // printf("error: %f\t", error);
    // printf("distance: %f\t", distance);
    // printf("b->distance: %f\n", b->distance);

    // normalise the inovation vector
    float norm = invSqrt(inovation.x * inovation.x + inovation.y * inovation.y);
    inovation.x *= norm;
    inovation.y *= norm;

    // scale the inovation vector by the error magnitude

    inovation.x *= -error;
    inovation.y *= -error;

    return inovation;
}

Position_t update_pos(Position_t est, float k_gain)
{
    Position_t new_est;

    Vector_2f inovation1 = Beacon_innovation(&b1, est);
     Vector_2f inovation2 = Beacon_innovation(&b2, est);

     float weight = b1.variance / (b1.variance + b2.variance);

    inovation1.x *= 1 - weight;;
    inovation1.y *= 1 - weight;;

    inovation2.x *= weight;
    inovation2.y *= weight;

    float K_boost = 1 + 3/(1+ b1.variance * b1.variance) + 3/(1+ b2.variance * b2.variance);

    new_est.x = est.x + k_gain * K_boost *  (inovation1.x + inovation2.x);
    new_est.y = est.y + k_gain * K_boost * (inovation1.y + inovation2.y);
    // printf("new_est.x: %f\t", new_est.x);
    // printf("new_est.y: %f\t", new_est.y);

    return new_est;
}