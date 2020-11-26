#ifndef TEAM3_GRAPH_H
#define TEAM3_GRAPH_H

#include <map>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include "components/graph/Node.h"
#include "components/graph/Edge.h"

class Graph {
private:
    int idx_;
    std::string name_;
public:
    std::map<int, std::unique_ptr<Node>> nodes;
    std::map<int, std::unique_ptr<Edge>> edges;
    std::unordered_map<int, std::vector<int> > adjacencyList;
    Graph(int idx, std::string name);
//    ~Graph();
    void addNode(std::unique_ptr<Node> node);
    void addEdge(std::unique_ptr<Edge> edge);
};

#endif //TEAM3_GRAPH_H
