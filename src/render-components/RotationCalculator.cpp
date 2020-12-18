#include <RotationCalculator.h>

Point RotationCalculator::calcUpperLineP1(Point p1, Point p2, float d) {
    float diag = calcDiagonal(p1, p2);
    float x = p2.x + calcBias(p1.y, p2.y, d, diag);
    float y = p2.y - calcBias(p1.x, p2.x, d, diag);
    return Point(x, y);
}

Point RotationCalculator::calcUpperLineP2(Point p1, Point p2, float d) {
    float diag = calcDiagonal(p1, p2);
    float x = p1.x + calcBias(p1.y, p2.y, d, diag);
    float y = p1.y - calcBias(p1.x, p2.x, d, diag);
    return Point(x, y);
}

Point RotationCalculator::calcLowerLineP1(Point p1, Point p2, float d) {
    float diag = calcDiagonal(p1, p2);
    float x = p2.x - calcBias(p1.y, p2.y, d, diag);
    float y = p2.y + calcBias(p1.x, p2.x, d, diag);
    return Point(x, y);
}

Point RotationCalculator::calcLowerLineP2(Point p1, Point p2, float d) {
    float diag = calcDiagonal(p1, p2);
    float x = p1.x - calcBias(p1.y, p2.y, d, diag);
    float y = p1.y + calcBias(p1.x, p2.x, d, diag);
    return Point(x, y);
}

float RotationCalculator::calcDiagonal(Point p1, Point p2) {
    return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

float RotationCalculator::calcBias(float z1, float z2, float d, float diag) {
    return d*(z2-z1) / diag;
}

Point RotationCalculator::calcPointOnLine(Point p1, Point p2, float ratio) {
    float x = p1.x+(p2.x - p1.x)*ratio;
    float y = p1.y+(p2.y - p1.y)*ratio;
    return Point(x, y);
}

float RotationCalculator::calcTrainRotation(Point p1, Point p2) {
    float x = p2.x - p1.x;
    float y = p2.y - p1.y;
    if (x == 0) {
        return 0;
    } else {
        return radToDeg(atan(y / x))+90;
    }
}

float RotationCalculator::radToDeg(float rad) {
    return rad*(180.0/M_PI);
}
