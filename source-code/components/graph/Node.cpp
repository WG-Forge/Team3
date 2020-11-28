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

void Node::setPost(std::unique_ptr<Post> post) {
    post_ = std::move(post);
}

Post *Node::getPost() {
    return post_.get();
}
