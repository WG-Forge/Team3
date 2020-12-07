#include <Node.h>

Node::Node(int32_t pointIdx, int32_t postIdx, Point coordinates) :
            pointIdx_(pointIdx), postIdx_(postIdx), coordinates_(coordinates) {}

int32_t Node::getPointIdx() const {
    return pointIdx_;
}

int32_t Node::getPostIdx() const {
    return postIdx_;
}

Point Node::getCoordinates() const {
    return coordinates_;
}

void Node::addNeighbor(Edge* incidentEdge) {
    neighbors_.push_back(incidentEdge);
}
