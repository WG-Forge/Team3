#include "Edge.h"

Edge::Edge(int idx, int length, std::shared_ptr<Node> firstNode, std::shared_ptr<Node> secondNode)
                                        : idx_(idx)
                                        , length_(length)
                                        , firstNode_(firstNode)
                                        , secondNode_(secondNode) {}

void Edge::setShape(std::unique_ptr<Shape> shape) {
    shape_ = std::move(shape);
}

void Edge::draw(DrawingStrategy* strategy) {
    shape_->draw(strategy);
}
