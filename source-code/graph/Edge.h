#ifndef TEAM3_EDGE_H
#define TEAM3_EDGE_H

#include <memory>

#include <graph/Node.h>

class Edge {
private:
    int idx_;
    double length_;
    Node* firstNode_;
    Node* secondNode_;
public:
    Edge(int idx, double length, Node* firstNode, Node* secondNode);
    double getLength() const;
    int getIndex() const;
    Node* getFirstNode();
    Node* getSecondNode();
    int getId();
};


#endif //TEAM3_EDGE_H
