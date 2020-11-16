#include "MinimalisticDrawingStrategy.h"

MinimalisticDrawingStrategy::MinimalisticDrawingStrategy()
                        : DrawingStrategy("background:rgba(0, 0, 0, 0);")
                        , penColor_(Qt::black)
                        , brushColor_(Qt::yellow) {}

void MinimalisticDrawingStrategy::drawLine(Point p1, Point p2) {
    painter_->setPen(QPen(penColor_, 2));
    painter_->drawLine(p1.x, p1.y, p2.x, p2.y);
}

void MinimalisticDrawingStrategy::drawCircle(Point center, int r) {
    painter_->setPen(QPen(penColor_, 2));
    painter_->setBrush(brushColor_);
    painter_->drawEllipse(center.x-r, center.y-r, 2*r, 2*r);
}