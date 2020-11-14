//
// Created by apple on 11/14/20.
//

#ifndef TEAM3_LINE_H
#define TEAM3_LINE_H


#include "Shape.h"

class Line : public Shape {
private:
    Point p1_;
    Point p2_;
public:
    Line(Point p1, Point p2);
    virtual void draw(DrawingStrategy* strategy);
};


#endif //TEAM3_LINE_H
