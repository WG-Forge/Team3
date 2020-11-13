#include "BasicDrawing.h"

BasicDrawing::BasicDrawing(QPainter* painter) : painter_(painter) { }

void BasicDrawing::drawLine(Point p1, Point p2) {
    painter_->drawLine(p1.x, p1.y, p2.x, p2.y);
}

void BasicDrawing::drawCircle(Point center, double r) {
    painter_->drawEllipse(center.x-r, center.y-r, 2*r, 2*r);
}