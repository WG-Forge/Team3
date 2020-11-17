#ifndef TEAM3_POINT_H
#define TEAM3_POINT_H


struct Point {
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) {}
    Point(Point* p) : x(p->x), y(p->y) {}
};


#endif //TEAM3_POINT_H
