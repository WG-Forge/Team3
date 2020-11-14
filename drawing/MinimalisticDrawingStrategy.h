#ifndef TEAM3_MINIMALISTICDRAWINGSTRATEGY_H
#define TEAM3_MINIMALISTICDRAWINGSTRATEGY_H

#include <QPainter>
#include "DrawingStrategy.h"

class MinimalisticDrawingStrategy : public DrawingStrategy {
public:
    virtual void drawLine(Point p1, Point p2);
    virtual void drawCircle(Point center, int r);
};


#endif //TEAM3_MINIMALISTICDRAWINGSTRATEGY_H
