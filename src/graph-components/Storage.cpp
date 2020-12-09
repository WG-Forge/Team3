#include <Storage.h>

Storage::Storage(int32_t pointIdx, int32_t postIdx, Point coordinates, uint32_t armorCapacity, uint32_t replenishment,
                 uint32_t armor, std::string name) :
        Node(pointIdx, postIdx, coordinates), name_(std::move(name)), armorCapacity_(armor),
        replenishment_(replenishment) {
    armor_ = armor;
}

uint32_t Storage::getArmorCapacity() const {
    return armorCapacity_;
}

uint32_t Storage::getReplenishment() const {
    return replenishment_;
}

uint32_t Storage::getArmor() const {
    return armor_;
}

const std::string& Storage::getName() const {
    return name_;
}

void Storage::setArmor(uint32_t armor) {
    armor_ = armor;
}
