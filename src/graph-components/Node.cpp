#include <Node.h>
#include <Edge.h>

Node::Node(int32_t pointIdx, int32_t postIdx, uint32_t type) :
            pointIdx_(pointIdx), postIdx_(postIdx), type_(type) {}

uint32_t Node::getType() const {
    return type_;
}

int32_t Node::getPointIdx() const {
    return pointIdx_;
}

int32_t Node::getPostIdx() const {
    return postIdx_;
}

Point Node::getCoordinates() const {
    return coordinates_;
}

std::vector<Edge*>& Node::getNeighbors() {
    return neighbors_;
}

void Node::setCoordinates(uint32_t x, uint32_t y) {
    coordinates_.x = x;
    coordinates_.y = y;
}

void Node::addNeighbor(Edge* incidentEdge) {
    neighbors_.push_back(incidentEdge);
}
