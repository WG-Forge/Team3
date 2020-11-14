#include "Line.h"

Line::Line(Point p1, Point p2)
        : p1_(p1)
        , p2_(p2) {}

void Line::draw(DrawingStrategy* strategy) {
    drawLine(p1_, p2_, strategy);
}