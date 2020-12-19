#ifndef TEAM3_MOVEAGENT_H
#define TEAM3_MOVEAGENT_H

#include <Node.h>
#include <game-components/Train.h>
#include <set>
#include "GraphAgent.h"

struct TrainMovement {
    int32_t lineIdx;
    int32_t speed;
    int32_t trainIdx;

    TrainMovement(int32_t lineIdx, int32_t speed, int32_t trainIdx);
};

class MoveAgent {
private:
    const int INF = 1000000000;
    Node* moveTo(GraphAgent* graphAgent, Train* train, uint32_t buildingType);
    TrainMovement calcMovement(GraphAgent* graphAgent, Train* train, Node* nextNode);
public:
    TrainMovement move(GraphAgent* graphAgent, Train* train);
};


#endif //TEAM3_MOVEAGENT_H
