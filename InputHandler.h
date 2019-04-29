//
// Created by devin on 4/28/19.
//

#ifndef AIFINAL_INPUTHANDLER_H
#define AIFINAL_INPUTHANDLER_H

struct Wall {
    int distance;
    int height;
};

class InputHandler {
public:
    int getTargetDistance();
    Wall getWallDimensions();

private:
    const int MIN_TARGET_DISTANCE = 10;
    const int MAX_TARGET_DISTANCE = 255;
};


#endif //AIFINAL_INPUTHANDLER_H
