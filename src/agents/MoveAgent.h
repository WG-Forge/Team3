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

class MoveAgent {
private:
    const int32_t INF = INT32_MAX;
    const std::vector<int> M1 {57, 58, 59, 60, 70, 80, 90, 89, 88, 87, 77, 67};
    const std::vector<int> M2 {66, 65, 64, 63, 73, 83, 93, 94, 95, 96, 86, 76};
    const std::vector<int> M3 {147, 148, 149, 150, 140, 130 ,120, 119, 118, 117, 127, 137};
    const std::vector<int> M4 {156, 155, 154, 153, 143, 133, 123, 124, 125, 126, 136, 146};
    const std::vector< std::vector<int> > marketCycles {M1, M2, M3, M4};

    const std::vector<int> S1 {57, 58, 59, 60, 61, 71, 81, 91, 101, 100, 99, 98, 97, 87, 77, 67};
    const std::vector<int> S2 {66, 65, 64, 63, 62, 72, 82, 92, 102, 103, 104, 105, 106, 96, 86, 76};
    const std::vector<int> S3 {147, 148, 149, 150, 151, 141, 131 ,121, 111, 110, 109, 108, 107, 117, 127, 137};
    const std::vector<int> S4 {156, 155, 154, 153, 152, 142, 132, 122, 112, 113, 114, 115, 116, 126, 136, 146};
    const std::vector< std::vector<int> > storageCycles {S1, S2, S3, S4};

    int getNextIndex(int currentIndex, int vectorSize);

    Node* getNextNodeCycles(std::vector<Node*>& graph,
                            const std::map<int32_t, uint32_t>& pointIdxCompression,
                              Train* train, int32_t buildingType, uint32_t homeIdx);
    TrainMovement calcMovement(Train* train, Node* nextNode);

public:
    std::vector<TrainMovement> moveAll(std::vector<Node*>& graph,
                 const std::map<int32_t, uint32_t>& pointIdxCompression,
                 Hometown* home);

    TrainMovement move(std::vector<Node*>& graph,
                       const std::map<int32_t, uint32_t>& pointIdxCompression,
                       Train* train,
                       uint32_t building,
                       Hometown* home);

    bool isSelfTrainsCollisionOccurs(TrainMovement movement, Hometown* home, Train* currentTrain);
    bool isTownOverProduct(TrainMovement movement, Hometown* home, Train* currentTrain);
    bool isSafeToLeaveNode(TrainMovement movement, Hometown* home, Train* currentTrain);

};
