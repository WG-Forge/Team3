#include <Hometown.h>

std::vector<Train>& Hometown::getHometownTrains() {
    return trains_;
}

void Hometown::addTrain(int32_t idx, int32_t lineIdx, uint32_t position, int32_t speed, uint32_t nextLevelPrice,
                        uint32_t goodsCapacity, uint32_t fuelCapacity, uint32_t fuelConsumption, uint32_t fuel,
                        uint32_t goods, Train::GoodsType goodsType, uint32_t level, std::string playerIdx, bool isMine,
                        uint32_t cooldown) {
    trains_.emplace_back(idx, lineIdx, position, speed, nextLevelPrice, goodsCapacity, fuelCapacity,
                      fuelConsumption, fuel, goods, goodsType, level, std::move(playerIdx), isMine, cooldown);
}

void Hometown::addTrain(const Train& train) {
    trains_.push_back(train);
}
