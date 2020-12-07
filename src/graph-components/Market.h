#pragma once

#include <string>
#include <Node.h>

class Market : public Node {
public:
    constexpr static uint32_t TYPE = 2;

private:
    const uint32_t productCapacity_;
    const uint32_t replenishment_;

    uint32_t product_;

    const std::string name_;

public:
    Market() = delete;
    Market(int32_t pointIdx, int32_t postIdx, Point coordinates, uint32_t productCapacity,
           uint32_t replenishment, uint32_t product, std::string name);

    uint32_t getProductCapacity() const;
    uint32_t getReplenishment() const;

    uint32_t getProduct() const;

    std::string getName() const;

    void setProduct(uint32_t product);
};
