#ifndef TEAM3_ROTATIONCALCULATOR_H
#define TEAM3_ROTATIONCALCULATOR_H

#include <math.h>
#include "Point.h"

class RotationCalculator {
private:
    double calcDiagonal(Point p1, Point p2);
    double calcBias(int z1, int z2, int d, double diag);
public:
    Point calcUpperLineP1(Point p1, Point p2, int d);
    Point calcUpperLineP2(Point p1, Point p2, int d);
    Point calcLowerLineP1(Point p1, Point p2, int d);
    Point calcLowerLineP2(Point p1, Point p2, int d);
};


#endif //TEAM3_ROTATIONCALCULATOR_H
