#include "Graph.h"

Graph::Graph(int idx, std::string name)
                                    : idx_(idx)
                                    , name_(name) {}

void Graph::addNode(std::shared_ptr<Node> node) {
    nodes.push_back(std::shared_ptr<Node>(node));
}

void Graph::addEdge(std::unique_ptr<Edge> edge) {
    edges.push_back(std::unique_ptr<Edge>(std::move(edge)));
}

void Graph::draw(DrawingStrategy* strategy) {
    for (auto node : nodes) {
        node->draw(strategy);
    }
    for (auto const& edge : edges) {
        edge->draw(strategy);
    }
}
