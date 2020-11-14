#include "Graph.h"

Graph::Graph(int idx, std::string name)
                                    : idx_(idx)
                                    , name_(name) { }

void Graph::addNode(std::unique_ptr<Node> node) {
    nodes_.push_back(std::unique_ptr<Node>(std::move(node)));
}

void Graph::addEdge(std::unique_ptr<Edge> edge) {
    edges_.push_back(std::unique_ptr<Edge>(std::move(edge)));
}
