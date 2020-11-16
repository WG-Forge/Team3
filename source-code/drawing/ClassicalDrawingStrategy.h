#ifndef TEAM3_CLASSICALDRAWINGSTRATEGY_H
#define TEAM3_CLASSICALDRAWINGSTRATEGY_H

#include <memory>
#include "Point.h"
#include "DrawingStrategy.h"
#include "RotationCalculator.h"

class ClassicalDrawingStrategy : public DrawingStrategy  {
private:
    std::unique_ptr<RotationCalculator> r_;
    int railwayWidth_;
    QColor penColor_;
public:
    ClassicalDrawingStrategy();
    virtual void drawLine(Point p1, Point p2);
    virtual void drawCircle(Point center, int r);
};


#endif //TEAM3_CLASSICALDRAWINGSTRATEGY_H
