#include "Graph.h"
#include "iostream"

Graph::Graph(int idx, std::string name)
                                    : idx_(idx)
                                    , name_(name) {}

void Graph::addEdge(std::unique_ptr<Edge> edge) {
    Edge* tempEdge = edge.get();
    adjacencyList[tempEdge->getFirstNode()->getId()].push_back(tempEdge->getSecondNode()->getId());
    adjacencyList[tempEdge->getSecondNode()->getId()].push_back(tempEdge->getFirstNode()->getId());
    edges[tempEdge->getId()] = std::unique_ptr<Edge>(std::move(edge));
}

void Graph::addNode(std::unique_ptr<Node> node) {
    Node* tempNode = node.get();
    nodes[tempNode->getId()] = std::unique_ptr<Node>(std::move(node));
}

//Graph::~Graph() {
//    std::cout << "graph was died\n";
//}
