//
// Created by devin on 5/1/19.
//

#include "Ai.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include "Plotter.h"
//#include "ProjCalculations.h"

Ai::Ai(float targetDistance, Wall wall) {
    this->targetDistance = targetDistance;
    this->wall = wall;

    if (targetDistance < 20.0) {
        neighborhood = PI/2.0;
        neighborhood_change = 0.95 + (wall.height/targetDistance)*0.005;
        if (neighborhood_change > 0.99) {neighborhood_change = 0.99;}
    }
    else if (targetDistance < 40.0) { neighborhood_change = 0.95 + (wall.height/targetDistance)*0.008;}
    else { neighborhood_change = 0.95;}

    if(DEBUG) {std::cout << "neighborhood_change:" << neighborhood_change << std::endl; std::cout << "factor: " << wall.height/targetDistance << std::endl;}
}

float Ai::findAngle() {
    srand(time(NULL)); // seeding random number generator
    currentGuess.angle = (rand() % 45 + 45) * PI / 180.0; // generate angle between 45 and 89 degrees, convert to radians

    std::random_device randDevice;
    std::mt19937 gen(randDevice());
    std::uniform_real_distribution<float> randDis(0.0, PI/4.0);
    currentGuess.angle = PI/4.0 + randDis(gen);


    currentGuess.distanceError = distanceFromGoal(currentGuess.angle, wall, targetDistance); // obtain initial error
    Plotter plotter;
    plotter.createPlot(currentGuess.angle, targetDistance, wall);

    for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++){
        // If "close enough" to the target, return that angle
        if (currentGuess.distanceError <= ERROR_THRESHOLD){
            if (DEBUG) {std::cout << "currentGuess angle: " << currentGuess.angle << " deg: "<< currentGuess.angle * 180.0/PI << "\terror: " << currentGuess.distanceError << std::endl;}
            std::cout << "Decision reached in " << iteration << " iterations.\n";
            return currentGuess.angle;
        }

        float increment = randDis(gen);
        if (increment > neighborhood) {increment = neighborhood;}

        // newGuess.angle is equal to currentGuess.angle +/- neighborhood degrees
        if (rand() % 2 == 1) {
            //newGuess.angle = currentGuess.angle + (rand() % (int)neighborhood) * PI / 180.0;
            //if (newGuess.angle*180.0/PI >= 90.0) {newGuess.angle = 89.0*PI/180.0;}
            newGuess.angle = currentGuess.angle + increment;
            if (newGuess.angle >= PI/2.0) {newGuess.angle = PI/2.0 - 0.01;}
        }
        else {
            //newGuess.angle = currentGuess.angle - (rand() % (int)neighborhood) * PI / 180.0;
            //if (newGuess.angle*180.0/PI < 45.0) {newGuess.angle = 45.0*PI/180.0;}
            newGuess.angle = currentGuess.angle - increment;
            if (newGuess.angle <= PI/4.0) {newGuess.angle = PI/4.0;}
        }

        newGuess.distanceError = distanceFromGoal(newGuess.angle, wall, targetDistance);
        errorDifference = newGuess.distanceError - currentGuess.distanceError;
        plotter.createPlot(newGuess.angle, targetDistance, wall);

        if (DEBUG){
            std::cout << "iteration: " << iteration << std::endl;
            std::cout << "currentGuess angle: " << currentGuess.angle << " deg: "<< currentGuess.angle * 180.0/PI << "\terror: " << currentGuess.distanceError << std::endl;
            std::cout << "newGuess angle: " << newGuess.angle << " deg: "<< newGuess.angle * 180.0/PI << "\terror: " << newGuess.distanceError << std::endl;
            std::cout << "neighborhood: " << neighborhood <<  "\tdegrees: " << neighborhood*180.0/PI << std::endl;
            std::cout << "temperature: " << temperature << "\n\n";
        }

        if (errorDifference < 0.0 || pow(EULER, -errorDifference/temperature) >= ((float)rand() / (float)RAND_MAX)){
            currentGuess = newGuess;
        }

        temperature *= TEMP_CHANGE;
        neighborhood *= neighborhood_change;
    }

    std::cout << "Decision timed out with " << MAX_ITERATIONS << " iterations.\n";
    return currentGuess.angle;
}
