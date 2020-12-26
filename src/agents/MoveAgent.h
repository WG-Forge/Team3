#pragma once

#include <set>
#include <Node.h>
#include <Train.h>
#include <GraphAgent.h>
#include <cmath>

struct TrainMovement {
    int32_t lineIdx;
    int32_t speed;
    int32_t trainIdx;

    TrainMovement(int32_t lineIdx, int32_t speed, int32_t trainIdx);
};

struct PathSearchPreferences {
    bool isMovingToSpecificNode;
    int32_t buildingType;
    Node* destination;
    //bool doesCountingZeroReplenishment;

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
    NextNode moveTo(std::vector<Node*>& graph, const std::map<int32_t, uint32_t>& pointIdxCompression,
                 Train* train, PathSearchPreferences prefs);
    TrainMovement calcMovement(Train* train, Node* nextNode);

    bool checkForDestination(Node* node, PathSearchPreferences prefs);
    bool checkForTransit(Node* node, PathSearchPreferences prefs);
public:
    TrainMovement move(std::vector<Node*>& graph,
                       const std::map<int32_t, uint32_t>& pointIdxCompression,
                       Train* train,
                       Hometown* home);
};
