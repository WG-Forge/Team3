#ifndef TEAM3_EDGE_H
#define TEAM3_EDGE_H


#include <memory>
#include "Node.h"

class Edge {
private:
    int idx_;
    int length_;
    std::shared_ptr<Node> firstNode_;
    std::shared_ptr<Node> secondNode_;
    std::unique_ptr<Shape> shape_;
public:
    Edge(int idx, int length, std::shared_ptr<Node> firstNode, std::shared_ptr<Node> secondNode);
    void setShape(std::unique_ptr<Shape> shape);
    void draw(DrawingStrategy* strategy);
};


#endif //TEAM3_EDGE_H
