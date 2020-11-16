#ifndef TEAM3_GRAPH_H
#define TEAM3_GRAPH_H

#include <memory>
#include <vector>
#include <string>
#include "Node.h"
#include "Edge.h"

class Graph {
private:
    int idx_;
    std::string name_;
public:
    std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::unique_ptr<Edge>> edges;
    Graph(int idx, std::string name);
//    ~Graph();
    void addNode(std::shared_ptr<Node> node);
    void addEdge(std::unique_ptr<Edge> edge);
    void draw(DrawingStrategy* strategy);
};

#endif //TEAM3_GRAPH_H
