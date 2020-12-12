#include <agents/GraphAgent.h>

GraphAgent::GraphAgent() {
    edgeCreationHelpers_.reserve(150);
    graph_.reserve(100);
}

std::vector<Node*>& GraphAgent::getGraph() {
    return graph_;
}

Edge* GraphAgent::findEdge(uint32_t lineIdx) {
    return lineIdxToEdge_.at(lineIdx);
}

void GraphAgent::mapEdge(Edge* edge) {
    lineIdxToEdge_.insert(std::make_pair(edge->getLineIdx(), edge));
}