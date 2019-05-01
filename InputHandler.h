//
// Created by devin on 4/28/19.
//

#ifndef AIFINAL_INPUTHANDLER_H
#define AIFINAL_INPUTHANDLER_H

#include "ProjCalculations.h"
/*
struct Wall {
    int distance;
    int height;
};
*/
class InputHandler {
public:
    float getTargetDistance();
    Wall getWallDimensions(const int TARGET_DISTANCE);

private:

    const int MIN_TARGET_DISTANCE = 5;
    const int MAX_TARGET_DISTANCE = 91;
};


#endif //AIFINAL_INPUTHANDLER_H
