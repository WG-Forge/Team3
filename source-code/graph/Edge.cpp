#include "Edge.h"

Edge::Edge(int idx, double length, Node* firstNode, Node* secondNode)
                                        : idx_(idx)
                                        , length_(length)
                                        , firstNode_(firstNode)
                                        , secondNode_(secondNode) {}

double Edge::getLength() const {
    return length_;
}

int Edge::getIndex() const {
    return idx_;
}

Node *Edge::getFirstNode() {
    return firstNode_;
}

Node *Edge::getSecondNode() {
    return secondNode_;
}
