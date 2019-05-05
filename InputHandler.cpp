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
    std::cout << "Enter the distance (" << MIN_TARGET_DISTANCE << " - " << MAX_TARGET_DISTANCE << " meters) for the target: ";
    std::cin >> distance;

    while (std::cin.fail() || distance < MIN_TARGET_DISTANCE || distance > MAX_TARGET_DISTANCE){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter the distance (" << MIN_TARGET_DISTANCE << " - " << MAX_TARGET_DISTANCE << " meters) for the target: ";
        std::cin >> distance;
    }

    if (DEBUG) {std::cout << "TARGET_DISTANCE = " << distance << std::endl;}

    return distance;
}

// Gets a wall height and distance from the user.
// Mathematically checked to ensure it's still possible to hit the target.
Wall InputHandler::getWallDimensions(const int TARGET_DISTANCE) {
    const float ANGLE_TO_TARGET = angleForDistance(TARGET_DISTANCE); // angle (rads) >= 45 degrees that hits target
    const int MAX_WALL_HEIGHT = (int)peakHeight(ANGLE_TO_TARGET) - 1; // peak of projectile height
    Wall wall;

    // Get user input for wall height
    std::cout << "Enter the height (up to " << MAX_WALL_HEIGHT << " meters) for the wall: ";
    std::cin >> wall.height;
    while (std::cin.fail() || wall.height < 1 || wall.height > MAX_WALL_HEIGHT){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter the height (up to " << (int)MAX_WALL_HEIGHT << " meters) for the wall: ";
        std::cin >> wall.height;
    }

    // getting 1st and 2nd times where specified height is reached
    const float TIME_AT_HEIGHT = timeAtHeight(wall.height, ANGLE_TO_TARGET);
    const float TIME_AT_HEIGHT_2 = timeOfFlight(ANGLE_TO_TARGET) - TIME_AT_HEIGHT;

    // getting 1st and 2nd distances (X coordinate) where specified height is reached
    const float DISTANCE_AT_HEIGHT = distanceAtTime(TIME_AT_HEIGHT, ANGLE_TO_TARGET);
    const float DISTANCE_AT_HEIGHT_2 = distanceAtTime(TIME_AT_HEIGHT_2, ANGLE_TO_TARGET);

    // Debugging statements
    if (DEBUG){
        std::cout << "ANGLE_TO_TARGET = " << ANGLE_TO_TARGET << " degrees: " << ANGLE_TO_TARGET*180/PI << std::endl;
        std::cout << "MAX_WALL_HEIGHT = " << MAX_WALL_HEIGHT << std::endl;

        std::cout << "TIME_AT_HEIGHT = " << TIME_AT_HEIGHT << std::endl;
        std::cout << "TIME_AT_HEIGHT_2 = " << TIME_AT_HEIGHT_2 << std::endl;

        std::cout << "DISTANCE_AT_HEIGHT = " << DISTANCE_AT_HEIGHT << std::endl;
        std::cout << "DISTANCE_AT_HEIGHT_2 = " << DISTANCE_AT_HEIGHT_2 << std::endl;
    }

    // Get user input for wall distance
    std::cout << "Enter the distance (between " << (int)(DISTANCE_AT_HEIGHT + 1)
              << " and " << (int)DISTANCE_AT_HEIGHT_2 << " meters) for the wall: ";
    std::cin >> wall.distance;
    while (std::cin.fail() || wall.distance < (int)(DISTANCE_AT_HEIGHT + 1) || wall.distance > (int)DISTANCE_AT_HEIGHT_2){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter the distance (between " << (int)(DISTANCE_AT_HEIGHT + 1)
                 << " and " << (int)DISTANCE_AT_HEIGHT_2 << " meters) for the wall: ";
        std::cin >> wall.distance;
    }




    return wall;

}