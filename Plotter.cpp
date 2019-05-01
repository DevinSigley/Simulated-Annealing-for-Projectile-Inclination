//
// Created by devin on 5/1/19.
//

#include "Plotter.h"



void Plotter::createPlot(float angleRads, int targetDistance, Wall wall) {
    std::ostringstream os;
    os << "tee " << plots.size() << ".gp | gnuplot -persist";
    std::string plotDesc = os.str();
    Gnuplot plot(plotDesc);
    Gnuplot* gnuptr = &plot;
    plots.push_back(gnuptr);

    float coords[2];
    if (checkWallImpact(coords, angleRads, wall)){
        *plots.back() << createPoint(coords[0], coords[1]) << createTarget(targetDistance) << createWall(wall)
                      << createProjectileString(angleRads, targetDistance, wall) << "\n";
        std::cout << "Impact : (" << coords[0] << ", " << coords[1] << ")\n";
        std::cout << "Distance from target: " << distanceFromGoal(angleRads, wall, targetDistance) << std::endl;
    }
    else {
        *plots.back() << createTarget(targetDistance) << createWall(wall)
                      << createProjectileString(angleRads, targetDistance, wall) << "\n";
    }


}

// Returns a string which commands gnuplot to draw a line between the two points
std::string Plotter::createLineString(float x1, float y1, float x2, float y2, std::string color, int lineWeight){
    std::ostringstream os;
    os << "set arrow from " << x1 << "," << y1
       << " to " << x2 << "," << y2 << " nohead "
       << "lc rgb \"" << color << "\" lw " << lineWeight << ";";

    return os.str();
}

std::string Plotter::createWall(Wall wall){
    return createLineString(wall.distance, 0, wall.distance, wall.height, "black", 2);
}


std::string Plotter::createTarget(int distance){
    return createLineString(distance-1.5, 0, distance+1.5, 0, "red", 4);
}


std::string Plotter::createPoint(float x, float y){
    std::ostringstream os;
    os << "set label at " << x << ", " << y << "\"\""
       << " point pointtype 7;";
    return os.str();
}


// Returns a string which commands gnuplot to draw a projectile curve
std::string Plotter::createProjectileString(float angleRads, int targetDistance, Wall wall){
    std::ostringstream os;
    float distance = pow(INITIAL_VELOCITY, 2.0) * sin(2 * angleRads) / GRAVITY;  // calculates total horizontal distance
    float height = pow(INITIAL_VELOCITY, 2.0) * pow(sin(angleRads), 2.0) / (2 * GRAVITY);    // calculates peak height

//    if (distance <= 20){ distance = 20; }
//    distance *= 1.1; // have the graph window 10% larger than necessary
//    height *= 1.1;   // have the graph window 10% larger than necessary

    if (targetDistance <= 25) {distance = 30;}
    else {distance = 100;}
    height = 50;

    float coords[2];
    if (checkWallImpact(coords, angleRads, wall)){
        os << "plot [0:" << distance << "][0:" << height << "] "
           << "0 <= x && x <= " << coords[0] << " ? "
           << "tan(" << angleRads << ")*x -("
           << GRAVITY << "*x**2)/(2*"
           << INITIAL_VELOCITY << "**2*(cos("
           << angleRads << "))**2) : 1/0 tit 'projectile'";
    }

    else {
        os << "plot [0:" << distance << "][0:" << height << "] "
           << "tan(" << angleRads << ")*x -("
           << GRAVITY << "*x**2)/(2*"
           << INITIAL_VELOCITY << "**2*(cos("
           << angleRads << "))**2)"
           << " tit 'projectile'";
    }



    return os.str();

}