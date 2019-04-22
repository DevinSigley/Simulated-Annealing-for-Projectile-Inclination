#include <vector>
#include <utility>
#include <math.h>
#include <string.h>
#include "gnuplot-iostream.h"
#include <sstream>

// compile with g++ -std=c++11 main.cpp -o main -lboost_iostreams -lboost_system -lboost_filesystem

const float GRAVITY = 9.8;
const float PI = 3.14159;

std::string createLineString(float x1, float y1, float x2, float y2);

int main() {
    std::vector<std::pair<double,double>> data;
    data.emplace_back(-2,-0.8);
    data.emplace_back(-1,-0.4);
    data.emplace_back(0,-0);
    data.emplace_back(1,0.4);
    data.emplace_back(1,0.8);

    float angle = 45.0;
    float angleRads = angle * PI / 180.0;
    float initialVelocity = 20.0;

    Gnuplot projectileMotion("tee proj.gp | gnuplot -persist");
    std::string projFormula;
    std::ostringstream os;
    os << "tan(" << angleRads << ")*x -("
          << GRAVITY << "*x**2)/(2*"
          << initialVelocity << "**2*(cos("
          << angleRads << "))**2)";
    projFormula = os.str();
    projectileMotion << createLineString(20,0,20,10) << ";plot [0:100][0:20] " << projFormula << " tit 'projectile'\n";

    return 0;
}

// Returns a string which commands gnuplot to draw a line between the two points
std::string createLineString(float x1, float y1, float x2, float y2){
    std::ostringstream os;
    os << "set arrow from " << x1 << "," << y1
                       << " to " << x2 << "," << y2 << " nohead";

    return os.str();
}