#pragma once

#include <set>
#include <Node.h>
#include <Train.h>
#include <GraphAgent.h>
#include <TrainsAgent.h>
#include <Town.h>
#include <Market.h>
#include <Storage.h>
#include <cmath>

struct TrainMovement {
    const Edge* line;
    int32_t speed;
    uint32_t newPosition;
    uint32_t trainIdx;

    TrainMovement(const Edge* line, int32_t speed, uint32_t newPosition, uint32_t trainIdx);
};

struct PathSearchPreferences {
    bool isMovingToSpecificNode;
    int32_t buildingType;
    Node* destination;

    PathSearchPreferences(bool isMovingToSpecificNode, int32_t buildingType, Node *destination);
};

struct NextNode{
    Node* node;
    uint32_t totalPathLength;

    NextNode(Node *node, uint32_t totalPathLength);
    NextNode();
};

class MoveAgent {
private:
    const int32_t INF = INT32_MAX;
    NextNode getNextNode(std::vector<Node*>& graph, const std::map<int32_t, uint32_t>& pointIdxCompression,
                 Train* train, PathSearchPreferences prefs);
    TrainMovement calcMovement(Train* train, Node* nextNode);

    bool checkForDestination(Node* node, PathSearchPreferences prefs);
    bool checkForTransit(Node* node, PathSearchPreferences prefs);
public:
    std::vector<TrainMovement> moveAll(std::vector<Node*>& graph,
                 const std::map<int32_t, uint32_t>& pointIdxCompression,
                 Hometown* home);

    TrainMovement move(std::vector<Node*>& graph,
                       const std::map<int32_t, uint32_t>& pointIdxCompression,
                       Train* train,
                       uint32_t building,
                       Hometown* home);

    bool checkForSelfTrainsCollision(TrainMovement movement, Hometown* home, Train* currentTrain);
};
