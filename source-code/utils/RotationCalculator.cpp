#include "RotationCalculator.h"

#include <iostream>

Point RotationCalculator::calcUpperLineP1(Point p1, Point p2, int d) {
    double diag = calcDiagonal(p1, p2);
    int x = p2.x + calcBias(p1.y, p2.y, d, diag);
    int y = p2.y - calcBias(p1.x, p2.x, d, diag);
    return Point(x, y);
}

Point RotationCalculator::calcUpperLineP2(Point p1, Point p2, int d) {
    double diag = calcDiagonal(p1, p2);
    int x = p1.x + calcBias(p1.y, p2.y, d, diag);
    int y = p1.y - calcBias(p1.x, p2.x, d, diag);
    return Point(x, y);
}

Point RotationCalculator::calcLowerLineP1(Point p1, Point p2, int d) {
    double diag = calcDiagonal(p1, p2);
    int x = p2.x - calcBias(p1.y, p2.y, d, diag);
    int y = p2.y + calcBias(p1.x, p2.x, d, diag);
    return Point(x, y);
}

Point RotationCalculator::calcLowerLineP2(Point p1, Point p2, int d) {
    double diag = calcDiagonal(p1, p2);
    int x = p1.x - calcBias(p1.y, p2.y, d, diag);
    int y = p1.y + calcBias(p1.x, p2.x, d, diag);
    return Point(x, y);
}

double RotationCalculator::calcDiagonal(Point p1, Point p2) {
    return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

double RotationCalculator::calcBias(int z1, int z2, int d, double diag) {
    return d*(z2-z1) / diag;
}
