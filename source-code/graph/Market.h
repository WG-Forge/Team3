#ifndef TEAM3_MARKET_H
#define TEAM3_MARKET_H


#include <string>

class Market {
private:
    std::string name_;
    int product_;
    int product_capacity_;
    int replenishment_;
public:
    Market(const std::string &name, int product, int productCapacity, int replenishment);
};


#endif //TEAM3_MARKET_H
