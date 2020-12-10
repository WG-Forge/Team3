#include <agents/GraphAgent.h>

GraphAgent::GraphAgent() {
    edgeCreationHelpers_.reserve(150);
    graph_.reserve(100);
}

std::vector<Node*>& GraphAgent::getGraph() {
    return graph_;
}