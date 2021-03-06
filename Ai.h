//
// Created by devin on 5/1/19.
//

#ifndef AIFINAL_AI_H
#define AIFINAL_AI_H

#include "ProjCalculations.h"

struct Guess {
    float angle; // angle of guess, in radians
    float distanceError;
};

class Ai {
public:
    Ai(float targetDistance, Wall wall);
    float findAngle();

private:
    Guess currentGuess;
    Guess newGuess;
    float errorDifference;
    float temperature = 1.0;
    float neighborhood = PI/4.0; // newGuess must be within NEIGHBORHOOD degrees of currentGuess
    float targetDistance;
    Wall wall;
    const int MAX_ITERATIONS = 100; // max # of guesses
    float ERROR_THRESHOLD = 0.75; // how close we must get to the center of the target
    const float TEMP_CHANGE = 0.95;
    float neighborhood_change = 0.99;

};


#endif //AIFINAL_AI_H
