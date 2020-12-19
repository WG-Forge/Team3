#pragma once

#include <set>
#include <Node.h>
#include <Train.h>
#include <GraphAgent.h>

struct TrainMovement {
    int32_t lineIdx;
    int32_t speed;
    int32_t trainIdx;

    TrainMovement(int32_t lineIdx, int32_t speed, int32_t trainIdx);
};

class MoveAgent {
private:
    const int32_t INF = INT32_MAX;
    Node* moveTo(std::vector<Node*>& graph, std::map<int32_t, uint32_t>& pointIdxCompression,
                 Train* train, uint32_t buildingType);
    TrainMovement calcMovement(Train* train, Node* nextNode);
public:
    TrainMovement move(std::vector<Node*>& graph, std::map<int32_t, uint32_t>& pointIdxCompression, Train* train);
};
