#include "ClassicalDrawingStrategy.h"


void ClassicalDrawingStrategy::drawLine(Point p1, Point p2) {
    painter_->setPen(QPen(Qt::black, 1));
    painter_->drawLine(p1.x-2, p1.y-2, p2.x-2, p2.y-2);
    painter_->drawLine(p1.x+2, p1.y+2, p2.x+2, p2.y+2);
    painter_->setPen(QPen(Qt::black, 3, Qt::DotLine));
    painter_->drawLine(p1.x, p1.y, p2.x, p2.y);
}

void ClassicalDrawingStrategy::drawCircle(Point center, int r) {
    painter_->drawPixmap(
            center.x-r, center.y-r, 2*r, 2*r,
            QPixmap((":/images/circus.png"))
            );
}