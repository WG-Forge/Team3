#pragma once

#include <vector>
#include <unordered_map>
#include <Train.h>

class TrainsAgent {
private:
    std::unordered_map<int32_t, uint32_t> trainIdxCompression_;
    std::vector<Train*> trains_;

    friend class Observer;
public:
    ~TrainsAgent();

    std::vector<Train*>& getAllTrains();
    static Node* getTrainNode(Train* train);

    /*void addTrain(int32_t idx, int32_t lineIdx, uint32_t position, int32_t speed, uint32_t nextLevelPrice,
                  uint32_t goodsCapacity, uint32_t fuelCapacity, uint32_t fuelConsumption, uint32_t fuel,
                  uint32_t  goods, Train::GoodsType goodsType, uint32_t level, std::string playerIdx,
                  bool isMine, uint32_t cooldown = 0);*/
    void addTrain(Train* train);
};
