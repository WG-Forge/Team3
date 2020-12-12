#include <RotationCalculator.h>

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

Point RotationCalculator::calcLowerLineP1(Point p1, Point p2, int32_t d) {
    double diag = calcDiagonal(p1, p2);
    int x = p2.x - calcBias(p1.y, p2.y, d, diag);
    int y = p2.y + calcBias(p1.x, p2.x, d, diag);
    return Point(x, y);
}

Point RotationCalculator::calcLowerLineP2(Point p1, Point p2, int32_t d) {
    double diag = calcDiagonal(p1, p2);
    int x = p1.x - calcBias(p1.y, p2.y, d, diag);
    int y = p1.y + calcBias(p1.x, p2.x, d, diag);
    return Point(x, y);
}

double RotationCalculator::calcDiagonal(Point p1, Point p2) {
    return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

double RotationCalculator::calcBias(int32_t z1, int32_t z2, int32_t d, double diag) {
    return d*(z2-z1) / diag;
}
float RotationCalculator::calcTrainRotation(Point p1, Point p2) {
    double x = p2.x - p1.x;
    double y = p2.y - p1.y;
    if (x == 0) {
        return 0;
    } else {
        return radToDeg(atan(y / x))+90;
    }
}

double RotationCalculator::radToDeg(double rad) {
    return rad*(180.0/M_PI);
}
