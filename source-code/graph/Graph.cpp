#include "Graph.h"
#include "iostream"

Graph::Graph(int idx, std::string name)
                                    : idx_(idx)
                                    , name_(name) {
//    std::cout << "graph was born\n";
}

void Graph::addEdge(std::unique_ptr<Edge> edge) {
    edges.push_back(std::unique_ptr<Edge>(std::move(edge)));
}

void Graph::addNode(std::unique_ptr<Node> node) {
     nodes.push_back(std::unique_ptr<Node>(std::move(node)));
}

//Graph::~Graph() {
//    std::cout << "graph was died\n";
//}
