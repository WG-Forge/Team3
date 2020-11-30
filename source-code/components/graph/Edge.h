#ifndef TEAM3_EDGE_H
#define TEAM3_EDGE_H

#include <memory>
#include <components/graph/Node.h>

class Train;

class Edge {
private:
    int idx_;
    double length_;
    Node* firstNode_;
    Node* secondNode_;
public:
    Train* train = nullptr;
    Edge(int idx, double length, Node* firstNode, Node* secondNode);
    double getLength() const;
    int getIndex() const;
    Node* getFirstNode();
    Node* getSecondNode();
    int getId();
//    virtual void readLayer0()
};


#endif //TEAM3_EDGE_H
