#include "ClassicalDrawingStrategy.h"


ClassicalDrawingStrategy::ClassicalDrawingStrategy()
        : DrawingStrategy("background-image:url(:/resources/images/background-space.jpg);")
        , r_(std::make_unique<RotationCalculator>())
        , railwayWidth_(2)
        , penColor_ (Qt::red) {}

void ClassicalDrawingStrategy::drawLine(Point p1, Point p2) {
    painter_->setPen(QPen(penColor_, 1));
    Point upperP1 = r_->calcUpperLineP1(p1, p2, railwayWidth_);
    Point upperP2 = r_->calcUpperLineP2(p1, p2, railwayWidth_);
    Point lowerP1 = r_->calcLowerLineP1(p1, p2, railwayWidth_);
    Point lowerP2 = r_->calcLowerLineP2(p1, p2, railwayWidth_);
    painter_->drawLine(upperP1.x, upperP1.y, upperP2.x, upperP2.y);
    painter_->drawLine(lowerP1.x, lowerP1.y, lowerP2.x, lowerP2.y);
    painter_->setPen(QPen(penColor_, railwayWidth_*2,
                          Qt::DotLine, Qt::FlatCap));
    painter_->drawLine(p1.x, p1.y, p2.x, p2.y);
}

void ClassicalDrawingStrategy::drawCircle(Point center, int r) {
    painter_->drawPixmap(
            center.x-r, center.y-r, 2*r, 2*r,
            QPixmap((":/resources/images/circus.png"))
            );
}

