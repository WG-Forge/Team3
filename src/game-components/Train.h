#pragma once

#include <string>
#include <vector>
#include <Edge.h>

class Train {
public:
    enum GoodsType {
        NOTHING = 0,
        PRODUCTS = 2,
        ARMOR = 3
    };

private:
    const int32_t idx_;

    uint32_t cooldown_;

    int32_t lineIdx_;
    uint32_t position_;
    int32_t speed_;

    uint32_t nextLevelPrice_;
    uint32_t goodsCapacity_;
    uint32_t fuelCapacity_;

    uint32_t fuelConsumption_;

    uint32_t fuel_;
    uint32_t goods_;
    GoodsType goodsType_;
    uint32_t level_;

    const std::string playerIdx_;
    bool isMine_;

    Edge* attachedEdge_;

public:
    Train() = delete;
    Train(int32_t idx, int32_t lineIdx, uint32_t position, int32_t speed, uint32_t nextLevelPrice,
          uint32_t goodsCapacity, uint32_t fuelCapacity, uint32_t fuelConsumption, uint32_t fuel,
          uint32_t  goods, GoodsType goodsType, uint32_t level, std::string playerIdx,
          bool isMine, uint32_t cooldown = 0);

    int32_t getIdx() const;
    uint32_t getCooldown() const;
    int32_t getLineIdx() const;
    uint32_t getPosition() const;
    int32_t getSpeed() const;
    uint32_t getNextLevelPrice() const;
    uint32_t getGoodsCapacity() const;
    uint32_t getFuelCapacity() const;
    uint32_t getFuelConsumption() const;
    uint32_t getFuel() const;
    uint32_t getGoods() const;
    GoodsType getGoodsType() const;
    uint32_t getLevel() const;
    const std::string& getPlayerIdx() const;
    bool isMine() const;

    const Edge* getEdge() const;

    void setCooldown(uint32_t cooldown); //would be removed if cooldown is changed only while train crush
    void setPosition(uint32_t position);
    void setSpeed(int32_t speed);
    void setFuel(uint32_t fuel);
    void setAttachedEdge(Edge* edge);
    void setGoods(uint32_t goods);
    void setGoodsType(GoodsType goodsType);

    void buy(GoodsType goodsType, uint32_t amount);
    void upgrade(uint32_t level, uint32_t nextLevelPrice, uint32_t goodsCapacity, uint32_t fuelCapacity);
    void crush(int32_t lineIdx, uint32_t cooldown);
};
