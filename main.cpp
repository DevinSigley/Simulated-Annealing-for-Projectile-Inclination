#include <vector>
#include <utility>
#include <math.h>
#include <string.h>
#include "gnuplot-iostream.h"
#include <sstream>
#include "InputHandler.h"

// compile with g++ -std=c++11 *.cpp -o main -lboost_iostreams -lboost_system -lboost_filesystem

const float GRAVITY = 9.807;
const float PI = 3.14159;

std::string createLineString(float x1, float y1, float x2, float y2, std::string color);
std::string createProjectileString(float angleRads, float initialVelocity);

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

    InputHandler inputHandler;
    std::cout << inputHandler.getTargetDistance();

    Gnuplot projectileMotion("tee proj.gp | gnuplot -persist");
    std::string projFormula;
    std::ostringstream os;
    os << "tan(" << angleRads << ")*x -("
          << GRAVITY << "*x**2)/(2*"
          << initialVelocity << "**2*(cos("
          << angleRads << "))**2)";
    projFormula = os.str();
    //projectileMotion << createLineString(20,0,20,10) << ";plot [0:100][0:20] " << projFormula << " tit 'projectile'\n";
    projectileMotion << createLineString(20, 0, 20, 10, "red") << ";" << createProjectileString(angleRads, initialVelocity) << "\n";
    return 0;
}

// Returns a string which commands gnuplot to draw a line between the two points
std::string createLineString(float x1, float y1, float x2, float y2, std::string color){
    std::ostringstream os;
    os << "set arrow from " << x1 << "," << y1
                       << " to " << x2 << "," << y2 << " nohead "
                       << "lc rgb \"" << color << "\"";

    return os.str();
}

// Returns a string which commands gnuplot to draw a projectile curve
std::string createProjectileString(float angleRads, float initialVelocity){
    std::ostringstream os;
    float distance = pow(initialVelocity, 2.0) * sin(2 * angleRads) / GRAVITY;
    float height = pow(initialVelocity, 2.0) * pow(sin(angleRads), 2.0) / (2 * GRAVITY);

    distance *= 1.1;
    height *= 1.1;


    os << "plot [0:" << distance << "][0:" << height << "] "
       << "tan(" << angleRads << ")*x -("
       << GRAVITY << "*x**2)/(2*"
       << initialVelocity << "**2*(cos("
       << angleRads << "))**2)"
       << " tit 'projectile'";

    return os.str();

}
