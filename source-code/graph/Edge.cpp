#include "Edge.h"

Edge::Edge(int idx, int length, Node* firstNode, Node* secondNode)
                                        : idx_(idx)
                                        , length_(length)
                                        , firstNode_(firstNode)
                                        , secondNode_(secondNode) {}

Node *Edge::getFirstNode() {
    return firstNode_;
}

Node *Edge::getSecondNode() {
    return secondNode_;
}

int Edge::getId() {
    return idx_;
}
