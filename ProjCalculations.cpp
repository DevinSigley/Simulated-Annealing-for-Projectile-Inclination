//
// Created by devin on 4/29/19.
//

#include "ProjCalculations.h"

// Given an angle, returns the trajectory's peak height
float peakHeight(float angleRads){
    return pow(INITIAL_VELOCITY, 2.0) * pow(sin(angleRads), 2.0) / (2.0 * GRAVITY); // peak of projectile height
}

// Returns the angle (>= 45) in radians needed to reach a certain distance
// Assumes initial velocity is INITIAL_VELOCITY
float angleForDistance(float distance){
    return PI/2.0 - asin(GRAVITY * distance / pow(INITIAL_VELOCITY, 2.0)) / 2.0;
}

// Given a height, returns the time at that position.
float timeAtHeight(float height, float angleRads) {
    return (INITIAL_VELOCITY*sin(angleRads)-sqrt(pow(INITIAL_VELOCITY, 2.0)*pow(sin(angleRads), 2.0) - 2.0*GRAVITY*height))/GRAVITY;
}

// Given a time and angle, returns the horizontal distance of the projectile at that time
float distanceAtTime(float time, float angleRads){
    return time * INITIAL_VELOCITY * cos(angleRads);
}

// Given an x-coord, returns the corresponding y-coord
float heightAtDistance(float distance, float angleRads){
    return tan(angleRads) * distance - (GRAVITY * pow(distance, 2.0)) / (2.0 * pow(INITIAL_VELOCITY, 2.0) * pow(cos(angleRads), 2.0));
}

// Given an angle, returns total time of flight
float timeOfFlight(float angleRads){
    return 2.0 * INITIAL_VELOCITY * sin(angleRads) / GRAVITY;
}

// Returns true if projectile hits the wall.
// Stores potential impact location in coords.
bool checkWallImpact(float coords[2], float angleRads, Wall wall){
    float height = heightAtDistance(wall.distance, angleRads);
    coords[0] = wall.distance;
    coords[1] = height;

    if (height < 0) { return false; }
    return (height <= wall.height);
}

// Computes how far the projectile is from the goal upon its first collision.
// Projectile can either stop upon hitting a wall or hitting the ground.
float distanceFromGoal(float angleRads, Wall wall, float targetDistance){
    float impactCoords[2] = {-1.0, -1.0};

    // Hit the wall, so distance has a vertical component. Coords of impact recorded in impactCoords.
    if (checkWallImpact(impactCoords, angleRads, wall)){
        return (sqrt(pow(targetDistance - impactCoords[0], 2.0) + pow(impactCoords[1], 2.0)));
    }

    // Didn't hit the wall, so distance is just horizontal.
    else {
        return abs(targetDistance - distanceAtTime(timeOfFlight(angleRads), angleRads));
    }
}


