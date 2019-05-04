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
//    Gnuplot userPlot("tee user.gp | gnuplot -persist");
//    userPlot  << createPoint(10, 20) << createTarget(TARGET_DISTANCE) << createWall(userWall) << createProjectileString(angleForDistance(TARGET_DISTANCE), TARGET_DISTANCE) << "\n";

/*    Plotter plotter;
    for (int i = 1; i < 6; i++){
        plotter.createPlot(PI/16 * i, TARGET_DISTANCE, userWall);
    }
*/
    Ai ai(TARGET_DISTANCE, userWall);
    float finalAngle = ai.findAngle();
    std::cout << "The final selected angle was " << finalAngle*180.0/PI << " degrees.\n";
    //plotter.createPlot(PI/4, TARGET_DISTANCE, userWall);
    Plotter plotter;
    plotter.createPlot(finalAngle, TARGET_DISTANCE, userWall);

    return 0;
}

