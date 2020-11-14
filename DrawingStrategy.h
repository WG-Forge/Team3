#ifndef TEAM3_DRAWINGSTRATEGY_H
#define TEAM3_DRAWINGSTRATEGY_H

#include "Point.h"

class DrawingStrategy {
public:
    virtual ~DrawingStrategy() {};
    virtual void drawLine(Point p1, Point p2) = 0;
    virtual void drawCircle(Point center, double r) = 0;
};

#endif //TEAM3_DRAWINGSTRATEGY_H
