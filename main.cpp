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
std::string createProjectileString(float angleRads, float initialVelocity);

int main(int argc, char** argv) {

    if (argc == 2){
        if (strncmp(argv[1], "debug", 5) == 0) {DEBUG = true; std::cout << "DEBUG mode enabled.\n\n";}
    }

    float angle = 45.0;
    float angleRads = angle * PI / 180.0;
    float initialVelocity = 20.0;

    InputHandler inputHandler;
    const float TARGET_DISTANCE = inputHandler.getTargetDistance();
    Wall userWall;
    userWall = inputHandler.getWallDimensions(TARGET_DISTANCE);
    Gnuplot userPlot("tee user.gp | gnuplot -persist");
    userPlot << createTarget(TARGET_DISTANCE) << createWall(userWall) << createProjectileString(angleForDistance(TARGET_DISTANCE), INITIAL_VELOCITY) << "\n";

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
    /*
    os << "set arrow from " << distance-1.5 << "," << 0
       << " to " << distance+1.5 << "," << 0
       << " nohead lc rgb \"red\" lw 4;";
    return os.str();
     */
    return createLineString(distance-1.5, 0, distance+1.5, 0, "red", 4);
}


// Returns a string which commands gnuplot to draw a projectile curve
std::string createProjectileString(float angleRads, float initialVelocity){
    std::ostringstream os;
    float distance = pow(initialVelocity, 2.0) * sin(2 * angleRads) / GRAVITY;  // calculates total horizontal distance
    float height = pow(initialVelocity, 2.0) * pow(sin(angleRads), 2.0) / (2 * GRAVITY);    // calculates peak height

    distance *= 1.1; // have the graph window 10% larger than necessary
    height *= 1.1;   // have the graph window 10% larger than necessary


    os << "plot [0:" << distance << "][0:" << height << "] "
       << "tan(" << angleRads << ")*x -("
       << GRAVITY << "*x**2)/(2*"
       << initialVelocity << "**2*(cos("
       << angleRads << "))**2)"
       << " tit 'projectile'";

    return os.str();

}
