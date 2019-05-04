//
// Created by devin on 4/28/19.
//

#ifndef AIFINAL_PROJCALCULATIONS_H
#define AIFINAL_PROJCALCULATIONS_H

#include <math.h>

extern bool DEBUG; // enable via command-line argument to have various output
const float PI = 3.14159;
const float EULER = 2.71828;
const float GRAVITY = 9.80665; // m/s^2
const float INITIAL_VELOCITY = 30.0; // m/s

struct Wall {
    float distance;
    float height;
};


// Given an angle, returns the trajectory's peak height
float peakHeight(float angleRads);

// Returns the angle (>= 45) in radians to reach a certain distance
// Assumes initial velocity is INITIAL_VELOCITY
float angleForDistance(float distance);

// Given a height, returns the time at that position.
float timeAtHeight(float height, float angleRads);

// Given a time and angle, returns the horizontal distance of the projectile at that time
float distanceAtTime(float time, float angleRads);

// Given an x-coord, returns the corresponding y-coord
float heightAtDistance(float distance, float angleRads);

// Given an angle, returns total time of flight
float timeOfFlight(float angleRads);

// Returns true if projectile hits the wall.
// Stores potential impact location in coords.
bool checkWallImpact(float coords[2], float angleRads, Wall wall);

// Computes how far the projectile is from the goal upon its first collision.
// Projectile can either stop upon hitting a wall or hitting the ground.
float distanceFromGoal(float angleRads, Wall wall, float targetDistance);

#endif //AIFINAL_PROJCALCULATIONS_H
