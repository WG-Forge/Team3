#include "Node.h"

Node::Node(int idx, int post_idx)
                            : idx_(idx)
                            , post_idx_(post_idx) {}

void Node::setPosition(std::unique_ptr<Point> position) {
    position_ = std::move(position);
}

Point Node::getPosition() const {
    return Point(position_.get());
}

int Node::getId() {
    return idx_;
}
