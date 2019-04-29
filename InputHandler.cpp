//
// Created by devin on 4/28/19.
//

#include "InputHandler.h"
#include <iostream>
#include <limits>

// Gets the target distance from the user.
// Distance is within [MIN_TARGET_DISTANCE, MAX_TARGET_DISTANCE].
int InputHandler::getTargetDistance() {
    int distance;
    std::cout << "Enter the distance (" << MIN_TARGET_DISTANCE << " - " << MAX_TARGET_DISTANCE << ") for the target: ";
    std::cin >> distance;

    while (std::cin.fail() || distance < MIN_TARGET_DISTANCE || distance > MAX_TARGET_DISTANCE){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter the distance (" << MIN_TARGET_DISTANCE << " - " << MAX_TARGET_DISTANCE << ") for the target: ";
        std::cin >> distance;
    }

    return distance;
}

// Gets a wall height and distance from the user.
// Mathematically checked to ensure it's still possible to hit the target.
Wall InputHandler::getWallDimensions() {

}