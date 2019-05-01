#include <vector>
#include <utility>
#include <math.h>
#include <string.h>
#include <sstream>
#include "gnuplot-iostream.h"
#include "ProjCalculations.h"
#include "InputHandler.h"

// compile with g++ -std=c++11 *.cpp -o main -lboost_iostreams -lboost_system -lboost_filesystem


bool DEBUG = false;

std::string createLineString(float x1, float y1, float x2, float y2, std::string color, int lineWeight);
std::string createWall(Wall wall);
std::string createTarget(int distance);
std::string createPoint(int x, int y);
std::string createProjectileString(float angleRads, int targetDistance);

int main(int argc, char** argv) {

    if (argc == 2){
        if (strncmp(argv[1], "debug", 5) == 0) {DEBUG = true; std::cout << "DEBUG mode enabled.\n\n";}
    }

    InputHandler inputHandler;
    const float TARGET_DISTANCE = inputHandler.getTargetDistance();
    Wall userWall;
    userWall = inputHandler.getWallDimensions(TARGET_DISTANCE);
    Gnuplot userPlot("tee user.gp | gnuplot -persist");
    userPlot  << createPoint(10, 20) << createTarget(TARGET_DISTANCE) << createWall(userWall) << createProjectileString(angleForDistance(TARGET_DISTANCE), TARGET_DISTANCE) << "\n";

    return 0;
}

// Returns a string which commands gnuplot to draw a line between the two points
std::string createLineString(float x1, float y1, float x2, float y2, std::string color, int lineWeight){
    std::ostringstream os;
    os << "set arrow from " << x1 << "," << y1
                       << " to " << x2 << "," << y2 << " nohead "
                       << "lc rgb \"" << color << "\" lw " << lineWeight << ";";

    return os.str();
}

std::string createWall(Wall wall){
    return createLineString(wall.distance, 0, wall.distance, wall.height, "black", 2);
}


std::string createTarget(int distance){
    return createLineString(distance-1.5, 0, distance+1.5, 0, "red", 4);
}


std::string createPoint(int x, int y){
    std::ostringstream os;
    os << "set label at " << x << ", " << y << "\"\""
       << " point pointtype 7;";
    return os.str();
}


// Returns a string which commands gnuplot to draw a projectile curve
std::string createProjectileString(float angleRads, int targetDistance){
    std::ostringstream os;
    float distance = pow(INITIAL_VELOCITY, 2.0) * sin(2 * angleRads) / GRAVITY;  // calculates total horizontal distance
    float height = pow(INITIAL_VELOCITY, 2.0) * pow(sin(angleRads), 2.0) / (2 * GRAVITY);    // calculates peak height

//    if (distance <= 20){ distance = 20; }
//    distance *= 1.1; // have the graph window 10% larger than necessary
//    height *= 1.1;   // have the graph window 10% larger than necessary

    if (targetDistance <= 25) {distance = 30;}
    else {distance = 100;}
    height = 50;


    os << "plot [0:" << distance << "][0:" << height << "] "
       << "tan(" << angleRads << ")*x -("
       << GRAVITY << "*x**2)/(2*"
       << INITIAL_VELOCITY << "**2*(cos("
       << angleRads << "))**2)"
       << " tit 'projectile'";

    return os.str();

}
