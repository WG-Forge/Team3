#ifndef TEAM3_CIRCLE_H
#define TEAM3_CIRCLE_H


#include "Shape.h"

class Circle : public Shape {
private:
    Point center_;
    int r_;
public:
    Circle(Point center, int r);
    virtual void draw(DrawingStrategy* strategy);
};


#endif //TEAM3_CIRCLE_H
