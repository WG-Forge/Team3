#include <components/static/StaticStore.h>
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

void Node::readLayer0(Json::Value root) {
    auto & post_idx = root["post_idx"];
    post = (post_idx == nullptr) ? nullptr : StaticStore::posts[post_idx.asInt()];
}

