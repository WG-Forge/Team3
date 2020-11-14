#include "Shape.h"

void Shape::drawLine(Point p1, Point p2, DrawingStrategy* strategy) {
    strategy->drawLine(p1, p2);
}

void Shape::drawCircle(Point center, int r, DrawingStrategy* strategy) {
    strategy->drawCircle(center, r);
}