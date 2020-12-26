#include <Town.h>

Town::Town(int32_t pointIdx, int32_t postIdx, std::string playerIdx,
           uint32_t nextLevelPrice, uint32_t populationCapacity, uint32_t productCapacity, uint32_t armorCapacity,
           uint32_t level, uint32_t population, uint32_t product, uint32_t armor, std::string name, bool isMine) :
           Node(pointIdx, postIdx, Town::TYPE), playerIdx_(std::move(playerIdx)), name_(std::move(name)) {
    nextLevelPrice_ = nextLevelPrice;
    populationCapacity_ = populationCapacity;
    productCapacity_ = productCapacity;
    armorCapacity_ = armorCapacity;

    level_ = level;
    population_ = population;
    product_ = product;
    armor_ = armor;

    isMine_ = isMine;
}

const std::string& Town::getPlayerIdx() const {
    return playerIdx_;
}

uint32_t Town::getNextLevelPrice() const {
    return nextLevelPrice_;
}

uint32_t Town::getPopulationCapacity() const {
    return populationCapacity_;
}

uint32_t Town::getProductCapacity() const {
    return productCapacity_;
}

uint32_t Town::getArmorCapacity() const {
    return armorCapacity_;
}

uint32_t Town::getLevel() const {
    return level_;
}

uint32_t Town::getPopulation() const {
    return population_;
}

uint32_t Town::getProduct() const {
    return product_;
}

uint32_t Town::getArmor() const {
    return armor_;
}

const std::string& Town::getName() const {
    return name_;
}

bool Town::isMine() const {
    return isMine_;
}

void Town::setPopulation(uint32_t population) {
    population_ = population;
}

void Town::setProduct(uint32_t product) {
    product_ = product;
}

void Town::setArmor(uint32_t armor) {
    armor_ = armor;
}

void Town::upgrade(uint32_t level, uint32_t nextLevelPrice, uint32_t populationCapacity, uint32_t productCapacity,
                   uint32_t armorCapacity) {
    level_ = level;
    nextLevelPrice_ = nextLevelPrice;
    populationCapacity_ = populationCapacity;
    productCapacity_ = productCapacity;
    armorCapacity_ = armorCapacity;
}
