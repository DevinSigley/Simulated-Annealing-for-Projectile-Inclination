//
// Created by devin on 5/1/19.
//

#ifndef AIFINAL_PLOTTER_H
#define AIFINAL_PLOTTER_H

#include <vector>
#include <string>
#include <sstream>
#include "gnuplot-iostream.h"
#include "ProjCalculations.h"
#include "InputHandler.h"


class Plotter {
public:
    void createPlot(float angleRads, int targetDistance, Wall wall);
    std::string createLineString(float x1, float y1, float x2, float y2, std::string color, int lineWeight);
    std::string createWall(Wall wall);
    std::string createTarget(int distance);
    std::string createPoint(int x, int y);
    std::string createProjectileString(float angleRads, int targetDistance);
    std::vector<Gnuplot*> plots;
};


#endif //AIFINAL_PLOTTER_H
