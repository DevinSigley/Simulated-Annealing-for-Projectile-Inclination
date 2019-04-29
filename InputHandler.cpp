//
// Created by devin on 4/28/19.
//

#include "InputHandler.h"
#include <iostream>
#include <limits>
#include "ProjCalculations.h"

// Gets the target distance from the user.
// Distance is within [MIN_TARGET_DISTANCE, MAX_TARGET_DISTANCE].
float InputHandler::getTargetDistance() {
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
Wall InputHandler::getWallDimensions(const float ANGLE, const float INITIAL_VELOCITY, const int TARGET_DISTANCE) {
    const int MAX_WALL_HEIGHT = (int)peakHeight(ANGLE); // peak of projectile height
    const int MAX_WALL_DISTANCE = targetDistance * 0.8;
    Wall wall;

    std:cout << "Enter the height (up to " << MAX_WALL_HEIGHT << ") for the wall: ";
    std::cin >> wall.height;
    while (std::cin.fail() || wall.height < 1 || wall.height > MAX_WALL_HEIGHT){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std:cout << "Enter the height (up to " << (int)MAX_WALL_HEIGHT << ") for the wall: ";
        std::cin >> wall.height;
    }

    float angleToHitTarget = angleForDistance(TARGET_DISTANCE);
    const float TIME_AT_HEIGHT = timeAtHeight(wall.height, angleToHitTarget);

    std::cout << "Enter the distance (between "



}