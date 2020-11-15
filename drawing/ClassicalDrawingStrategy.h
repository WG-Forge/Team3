#ifndef TEAM3_CLASSICALDRAWINGSTRATEGY_H
#define TEAM3_CLASSICALDRAWINGSTRATEGY_H


#include "Point.h"
#include "DrawingStrategy.h"

class ClassicalDrawingStrategy : public DrawingStrategy  {
public:
    virtual void drawLine(Point p1, Point p2);
    virtual void drawCircle(Point center, int r);
};


#endif //TEAM3_CLASSICALDRAWINGSTRATEGY_H
