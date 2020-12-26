#include <TrainsAgent.h>


TrainsAgent::~TrainsAgent() {
    for (int32_t i = 0; i < trains_.size(); ++i) {
        delete trains_[i];
    }
}

std::vector<Train*>& TrainsAgent::getAllTrains() {
    return trains_;
}

/*void TrainsAgent::addTrain(int32_t idx, int32_t lineIdx, uint32_t position, int32_t speed, uint32_t nextLevelPrice,
                        uint32_t goodsCapacity, uint32_t fuelCapacity, uint32_t fuelConsumption, uint32_t fuel,
                        uint32_t goods, Train::GoodsType goodsType, uint32_t level, std::string playerIdx, bool isMine,
                        uint32_t cooldown) {
    trains_.emplace_back(idx, lineIdx, position, speed, nextLevelPrice, goodsCapacity, fuelCapacity,
                         fuelConsumption, fuel, goods, goodsType, level, std::move(playerIdx), isMine, cooldown);
}*/

void TrainsAgent::addTrain(Train* train) {
    trains_.push_back(train);
}

Node* TrainsAgent::getTrainNode(Train* train) {
    if (train->getPosition() == 0) {
        return train->getEdge()->getFirstNode();
    } else if (train->getPosition() == train->getEdge()->getLength()) {
        return train->getEdge()->getSecondNode();
    } else {
        return nullptr;
    }
}
