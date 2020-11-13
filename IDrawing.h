#ifndef TEAM3_IDRAWING_H
#define TEAM3_IDRAWING_H

#include "Point.h"

class IDrawing {
public:
    virtual ~IDrawing() {};
    virtual void drawLine(Point p1, Point p2) = 0;
    virtual void drawCircle(Point center, double r) = 0;
};

#endif //TEAM3_IDRAWING_H
