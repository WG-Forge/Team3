#ifndef TEAM3_EDGE_H
#define TEAM3_EDGE_H


#include <memory>
#include "Node.h"

class Edge {
private:
    int idx_;
    int length_;
    Node* firstNode_;
    Node* secondNode_;
public:
    Edge(int idx, int length, Node* firstNode, Node* secondNode);
    Node* getFirstNode();
    Node* getSecondNode();
    int getId();
};


#endif //TEAM3_EDGE_H
