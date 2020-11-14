#ifndef TEAM3_MINIMALISTICDRAWINGSTRATEGY_H
#define TEAM3_MINIMALISTICDRAWINGSTRATEGY_H

#include <QPainter>
#include "DrawingStrategy.h"

class MinimalisticDrawingStrategy : public DrawingStrategy {
private:
    QPainter* painter_;
public:
    explicit MinimalisticDrawingStrategy(QPainter* painter);
    virtual void drawLine(Point p1, Point p2);
    virtual void drawCircle(Point center, int r);
};


#endif //TEAM3_MINIMALISTICDRAWINGSTRATEGY_H
