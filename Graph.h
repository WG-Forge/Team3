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
    std::vector<std::shared_ptr<Node>> nodes_;
    std::vector<std::unique_ptr<Edge>> edges_;
public:
    Graph(int idx, std::string name);
    void addNode(std::unique_ptr<Node> node);
    void addEdge(std::unique_ptr<Edge> edge);
};

#endif //TEAM3_GRAPH_H
