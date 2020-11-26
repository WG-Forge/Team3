#ifndef TEAM3_MARKET_H
#define TEAM3_MARKET_H


#include <string>
#include "Post.h"

class Market : public Post {
private:
    int product_ = 0;
    int product_capacity_ = 0;
    int replenishment_ = 0;
public:
    explicit Market(int idx);
    void readLayer1(Json::Value root) override;
};


#endif //TEAM3_MARKET_H
