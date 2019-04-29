//
// Created by devin on 4/28/19.
//

#ifndef AIFINAL_PROJCALCULATIONS_H
#define AIFINAL_PROJCALCULATIONS_H

#include <math.h>

const float PI = 3.14159;
const float GRAVITY = 9.80665; // m/s^2
const float INITIAL_VELOCITY = 30.0; // m/s

// Given an angle, returns the trajectory's peak height
float peakHeight(float angleRads){
    return pow(INITIAL_VELOCITY, 2.0) * pow(sin(angleRads), 2.0) / (2 * GRAVITY); // peak of projectile height
}

// Returns the angle (>= 45) in radians to reach a certain distance
// Assumes initial velocity is INITIAL_VELOCITY
float angleForDistance(float distance){
    return PI/4 - asin(GRAVITY * distance / pow(INITIAL_VELOCITY, 2.0)) / 2;
}

// Given a height, returns the time at that position.
float timeAtHeight(float height, float angleRads) {
    return (INITIAL_VELOCITY*sin(pi/4)-sqrt(pow(INITIAL_VELOCITY, 2.0)*pow(sin(PI/4), 2.0) - 2*GRAVITY*height))/GRAVITY;
}

#endif //AIFINAL_PROJCALCULATIONS_H
