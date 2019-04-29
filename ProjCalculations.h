//
// Created by devin on 4/28/19.
//

#ifndef AIFINAL_PROJCALCULATIONS_H
#define AIFINAL_PROJCALCULATIONS_H

#include <math.h>

extern bool DEBUG; // enable via command-line argument to have various output
const float PI = 3.14159;
const float GRAVITY = 9.80665; // m/s^2
const float INITIAL_VELOCITY = 30.0; // m/s

// Given an angle, returns the trajectory's peak height
float peakHeight(float angleRads);

// Returns the angle (>= 45) in radians to reach a certain distance
// Assumes initial velocity is INITIAL_VELOCITY
float angleForDistance(float distance);

// Given a height, returns the time at that position.
float timeAtHeight(float height, float angleRads);

float distanceAtTime(float time, float angleRads);

float timeOfFlight(float angleRads);

#endif //AIFINAL_PROJCALCULATIONS_H
