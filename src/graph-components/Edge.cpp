#include <Edge.h>

Edge::Edge(int32_t lineIdx, uint32_t length, Node* firstNode, Node* secondNode) :
           lineIdx_(lineIdx), length_(length) {
    firstNode_ = firstNode;
    secondNode_ = secondNode;
}

int32_t Edge::getLineIdx() const {
    return lineIdx_;
}

uint32_t Edge::getLength() const {
    return length_;
}

Node* Edge::getFirstNode() const {
    return firstNode_;
}

Node* Edge::getSecondNode() const {
    return secondNode_;
}
