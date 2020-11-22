#ifndef TEAM3_MARKET_H
#define TEAM3_MARKET_H


#include <string>
#include "Node.h"

class Market : public Node {
private:
    std::string name_;
    int product_;
    int product_capacity_;
    int replenishment_;
    int idx_;
    int point_idx_;
public:
    Market(int idx, int point_idx, const std::string &name, int product, int productCapacity, int replenishment);
};


#endif //TEAM3_MARKET_H
