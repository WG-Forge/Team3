#pragma once

#include <cmath>
#include <Point.h>

class RotationCalculator {
private:
    float calcDiagonal(Point p1, Point p2);
    float calcBias(float z1, float z2, float d, float diag);
    float radToDeg(float rad);
public:
    Point calcUpperLineP1(Point p1, Point p2, float d);
    Point calcUpperLineP2(Point p1, Point p2, float d);
    Point calcLowerLineP1(Point p1, Point p2, float d);
    Point calcLowerLineP2(Point p1, Point p2, float d);

    float calcTrainRotation(Point p1, Point p2);
};
