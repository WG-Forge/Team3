#ifndef TEAM3_NODE_H
#define TEAM3_NODE_H


#include "../drawing/Shape.h"

class Node {
private:

    int post_idx_;
    std::unique_ptr<Shape> shape_;
public:
    int idx_;
    Node(int idx, int post_idx);
    void setShape(std::unique_ptr<Shape> shape);
    void draw(DrawingStrategy* strategy);
};


#endif //TEAM3_NODE_H
