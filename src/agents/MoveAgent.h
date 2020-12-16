#ifndef TEAM3_MOVEAGENT_H
#define TEAM3_MOVEAGENT_H

#include <Node.h>
#include <game-components/Train.h>
#include <set>

struct TrainMovement {
    int32_t lineIdx;
    int32_t speed;
    int32_t trainIdx;
};

class MoveAgent {
private:
    const int INF = 1000000000;
    int moveTo(const std::vector<Node *> &g, Train* train, uint32_t buildingType);
public:
    Node* move(const std::vector<Node*>& g, Train* train);
};


#endif //TEAM3_MOVEAGENT_H
