/*
 * Final Project for CSCI 5837 / Spring 2019
 * by: Devin Sigley
 * Uses simulated annealing to hit a target defined by the user.
 *
 * Requires Gnuplot and Boost
 * compile with g++ -std=c++11 *.cpp -o main -lboost_iostreams -lboost_system -lboost_filesystem
 */

#include <vector>
#include <utility>
#include <math.h>
#include <string.h>
#include <sstream>
#include "gnuplot-iostream.h"
#include "ProjCalculations.h"
#include "InputHandler.h"
#include "Plotter.h"
#include "Ai.h"


bool DEBUG = false;

int main(int argc, char** argv) {

    if (argc == 2){
        if (strncmp(argv[1], "debug", 5) == 0) {DEBUG = true; std::cout << "DEBUG mode enabled.\n\n";}
    }

    InputHandler inputHandler;
    const float TARGET_DISTANCE = inputHandler.getTargetDistance();
    Wall userWall;
    userWall = inputHandler.getWallDimensions(TARGET_DISTANCE);

    Ai ai(TARGET_DISTANCE, userWall); // initiate the AI
    float finalAngle = ai.findAngle(); // have the AI try to find an acceptable angle
    std::cout << "The final angle chosen was " << finalAngle*180.0/PI << " degrees.\n";
    std::cout << "It has an error of " << distanceFromGoal(finalAngle, userWall, TARGET_DISTANCE) << " meters.\n";

    Plotter plotter;
    plotter.createPlot(finalAngle, TARGET_DISTANCE, userWall);

    return 0;
}

