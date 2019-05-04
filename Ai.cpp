//
// Created by devin on 5/1/19.
//

#include "Ai.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Plotter.h"
//#include "ProjCalculations.h"

Ai::Ai(float targetDistance, Wall wall) {
    this->targetDistance = targetDistance;
    this->wall = wall;
}

float Ai::findAngle() {
    srand(time(NULL)); // seeding random number generator
    currentGuess.angle = (rand() % 45 + 45) * PI / 180.0; // generate angle between 45 and 89 degrees, convert to radians

    currentGuess.distanceError = distanceFromGoal(currentGuess.angle, wall, targetDistance); // obtain initial error
    Plotter plotter;
    plotter.createPlot(currentGuess.angle, targetDistance, wall);

    for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++){
        // If "close enough" to the target, return that angle
        if (currentGuess.distanceError <= ERROR_THRESHOLD){
            if (DEBUG) {std::cout << "currentGuess angle: " << currentGuess.angle << " deg: "<< currentGuess.angle * 180.0/PI << "\terror: " << currentGuess.distanceError << std::endl;}
            return currentGuess.angle;
        }

        // newGuess.angle is equal to currentGuess.angle +/- NEIGHBORHOOD degrees
        if (rand() % 2 == 1) { newGuess.angle = currentGuess.angle + (rand() % NEIGHBORHOOD) * PI / 180.0; }
        else { newGuess.angle = currentGuess.angle - (rand() % NEIGHBORHOOD) * PI / 180.0; }

        newGuess.distanceError = distanceFromGoal(newGuess.angle, wall, targetDistance);
        errorDifference = newGuess.distanceError - currentGuess.distanceError;
        plotter.createPlot(newGuess.angle, targetDistance, wall);

        if (DEBUG){
            std::cout << "iteration: " << iteration << std::endl;
            std::cout << "currentGuess angle: " << currentGuess.angle << " deg: "<< currentGuess.angle * 180.0/PI << "\terror: " << currentGuess.distanceError << std::endl;
            std::cout << "newGuess angle: " << newGuess.angle << " deg: "<< newGuess.angle * 180.0/PI << "\terror: " << newGuess.distanceError << std::endl;
            std::cout << "temperature: " << temperature << "\n\n";
        }

        if (errorDifference < 0.0 || pow(EULER, -errorDifference/temperature) >= ((float)rand() / (float)RAND_MAX)){
            currentGuess = newGuess;
        }

        temperature *= TEMP_CHANGE;
    }

    return currentGuess.angle;
}
