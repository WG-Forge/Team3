#ifndef TEAM3_SHAPE_H
#define TEAM3_SHAPE_H

#include <memory>
#include "DrawingStrategy.h"

class Shape {
protected:
    void drawLine(Point p1, Point p2, DrawingStrategy* strategy);
    void drawCircle(Point center, int r, DrawingStrategy* strategy);
public:
    virtual ~Shape() {}
    virtual void draw(DrawingStrategy* strategy) = 0;
};


#endif //TEAM3_SHAPE_H
