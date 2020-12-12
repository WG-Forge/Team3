#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <Point.h>

class RotationCalculator {
private:
    double calcDiagonal(Point p1, Point p2);
    double calcBias(int32_t z1, int32_t z2, int32_t d, double diag);
    double radToDeg(double rad);
public:
    Point calcUpperLineP1(Point p1, Point p2, int32_t d);
    Point calcUpperLineP2(Point p1, Point p2, int32_t d);
    Point calcLowerLineP1(Point p1, Point p2, int32_t d);
    Point calcLowerLineP2(Point p1, Point p2, int32_t d);

    float calcTrainRotation(Point p1, Point p2);
};
