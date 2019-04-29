//
// Created by devin on 4/29/19.
//

#include "ProjCalculations.h"

// Given an angle, returns the trajectory's peak height
float peakHeight(float angleRads){
    return pow(INITIAL_VELOCITY, 2.0) * pow(sin(angleRads), 2.0) / (2 * GRAVITY); // peak of projectile height
}

// Returns the angle (>= 45) in radians to reach a certain distance
// Assumes initial velocity is INITIAL_VELOCITY
float angleForDistance(float distance){
    return PI/2 - asin(GRAVITY * distance / pow(INITIAL_VELOCITY, 2.0)) / 2;
    //return asin(GRAVITY * distance / pow(INITIAL_VELOCITY, 2.0)) / 2;

}

// Given a height, returns the time at that position.
float timeAtHeight(float height, float angleRads) {
    return (INITIAL_VELOCITY*sin(angleRads)-sqrt(pow(INITIAL_VELOCITY, 2.0)*pow(sin(angleRads), 2.0) - 2*GRAVITY*height))/GRAVITY;
}

float distanceAtTime(float time, float angleRads){
    return time * INITIAL_VELOCITY * cos(angleRads);
}

float timeOfFlight(float angleRads){
    return 2 * INITIAL_VELOCITY * sin(angleRads) / GRAVITY;
}