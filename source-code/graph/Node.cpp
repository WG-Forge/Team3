#include "Node.h"

Node::Node(int idx, int post_idx)
                            : idx_(idx)
                            , post_idx_(post_idx) {}

void Node::setPosition(Point position) {
    position_ = position;
}

Point Node::getPosition() const {
    return position_;
}

int Node::getId() {
    return idx_;
}
