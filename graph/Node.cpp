#include "Node.h"

Node::Node(int idx, int post_idx)
                            : idx_(idx)
                            , post_idx_(post_idx) {}

void Node::setShape(std::unique_ptr<Shape> shape) {
    shape_ = std::move(shape);
}

void Node::draw(DrawingStrategy *strategy) {
    shape_->draw(strategy);
}
