#ifndef TEAM3_GRAPH_H
#define TEAM3_GRAPH_H

#include <map>
#include <memory>
#include <vector>
#include <string>

#include <graph/Node.h>
#include <graph/Edge.h>

class Graph {
private:
    int idx_;
    std::string name_;
public:
    std::vector<std::unique_ptr<Node>> nodes;
    std::vector<std::unique_ptr<Edge>> edges;
    Graph(int idx, std::string name);
//    ~Graph();
    void addNode(std::unique_ptr<Node> node);
    void addEdge(std::unique_ptr<Edge> edge);
};

#endif //TEAM3_GRAPH_H
