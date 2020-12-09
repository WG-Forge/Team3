#pragma once

#include <string>
#include <Node.h>

class Storage : public Node {
public:
    constexpr static uint32_t TYPE = 3;

private:
    const uint32_t armorCapacity_;
    const uint32_t replenishment_;

    uint32_t armor_;

    const std::string name_;

public:
    Storage() = delete;
    Storage(int32_t pointIdx, int32_t postIdx, Point coordinates, uint32_t productCapacity,
            uint32_t replenishment, uint32_t product, std::string name);

    uint32_t getArmorCapacity() const;
    uint32_t getReplenishment() const;

    uint32_t getArmor() const;

    const std::string& getName() const;

    void setArmor(uint32_t product);
};
