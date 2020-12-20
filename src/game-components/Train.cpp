#include <Train.h>

Train::Train(int32_t idx, int32_t lineIdx, uint32_t position, int32_t speed, uint32_t nextLevelPrice,
             uint32_t goodsCapacity, uint32_t fuelCapacity, uint32_t fuelConsumption, uint32_t fuel, uint32_t goods,
             Train::GoodsType goodsType, uint32_t level, std::string playerIdx, bool isMine, uint32_t cooldown) :
             idx_(idx), playerIdx_(std::move(playerIdx)) {
    lineIdx_ = lineIdx;
    position_ = position;
    speed_ = speed;

    nextLevelPrice_ = nextLevelPrice;
    goodsCapacity_ = goodsCapacity;
    fuelCapacity_ = fuelCapacity;

    fuelConsumption_ = fuelConsumption;

    fuel_ = fuel;
    goods_ = goods;
    goodsType_= goodsType;
    level_ = level;

    isMine_ = isMine;
    cooldown_ = cooldown;

    attachedEdge_ = nullptr;
}

int32_t Train::getIdx() const {
    return idx_;
}

uint32_t Train::getCooldown() const {
    return cooldown_;
}

int32_t Train::getLineIdx() const {
    return lineIdx_;
}

uint32_t Train::getPosition() const {
    return position_;
}

int32_t Train::getSpeed() const {
    return speed_;
}

uint32_t Train::getNextLevelPrice() const {
    return nextLevelPrice_;
}

uint32_t Train::getGoodsCapacity() const {
    return goodsCapacity_;
}

uint32_t Train::getFuelCapacity() const {
    return fuelCapacity_;
}

uint32_t Train::getFuelConsumption() const {
    return fuelConsumption_;
}

uint32_t Train::getFuel() const {
    return fuel_;
}

uint32_t Train::getGoods() const {
    return goods_;
}

Train::GoodsType Train::getGoodsType() const {
    return goodsType_;
}

uint32_t Train::getLevel() const {
    return level_;
}

const std::string& Train::getPlayerIdx() const{
    return playerIdx_;
}

bool Train::isMine() const {
    return isMine_;
}

const Edge* Train::getEdge() const {
    return attachedEdge_;
}

void Train::setCooldown(uint32_t cooldown) {
    cooldown_ = cooldown;
}

void Train::setPosition(uint32_t position) {
    position_ = position;
}

void Train::setSpeed(int32_t speed) {
    speed_ = speed;
}

void Train::setFuel(uint32_t fuel) {
    fuel_ = fuel;
}

void Train::setAttachedEdge(Edge* edge) {
    attachedEdge_ = edge;
    lineIdx_ = edge->getLineIdx();
}

void Train::buy(GoodsType goodsType, uint32_t goods) {
    goodsType_ = goodsType;
    goods_ = goods;
}

void Train::upgrade(uint32_t level, uint32_t nextLevelPrice, uint32_t goodsCapacity, uint32_t fuelCapacity) {
    level_ = level;
    nextLevelPrice_ = nextLevelPrice;
    goodsCapacity_ = goodsCapacity;
    fuelCapacity_ = fuelCapacity;
}

void Train::crush(int32_t lineIdx, uint32_t cooldown) {
    lineIdx_ = lineIdx;
    position_ = 0;
    speed_ = 0;
    cooldown_ = cooldown;
}
