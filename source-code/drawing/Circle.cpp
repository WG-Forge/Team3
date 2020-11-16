#include "Circle.h"

Circle::Circle(Point center, int r)
                        : center_(center)
                        , r_(r) {}


void Circle::draw(DrawingStrategy* strategy) {
    drawCircle(center_, r_, strategy);
}
