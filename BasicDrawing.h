#ifndef TEAM3_BASICDRAWING_H
#define TEAM3_BASICDRAWING_H

#include <QPainter>
#include "IDrawing.h"

class BasicDrawing : public IDrawing {
private:
    QPainter* painter_;
public:
    explicit BasicDrawing(QPainter* painter);
    virtual void drawLine(Point p1, Point p2);
    virtual void drawCircle(Point center, double r);
};


#endif //TEAM3_BASICDRAWING_H
