#pragma once

#include <Town.h>
#include <Train.h>

class Hometown : public Town {
private:
    std::vector<Train*> trains_;

public:
    Hometown() = delete;
    using Town::Town;

    bool isMine() = delete;
    std::vector<Train*>& getHometownTrains();

    /*void addTrain(int32_t idx, int32_t lineIdx, uint32_t position, int32_t speed, uint32_t nextLevelPrice,
                  uint32_t goodsCapacity, uint32_t fuelCapacity, uint32_t fuelConsumption, uint32_t fuel,
                  uint32_t  goods, Train::GoodsType goodsType, uint32_t level, std::string playerIdx,
                  bool isMine, uint32_t cooldown = 0);*/
    void addTrain(Train* train);
};
