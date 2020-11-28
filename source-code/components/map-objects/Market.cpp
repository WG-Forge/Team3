#include "Market.h"


Market::Market(int idx) : Post(idx, "resources/images/market.png") {}

void Market::readLayer1(Json::Value root) {
    Post::readLayer1(root);
    product_ = root["product"].asInt();
    product_capacity_ = root["product_capacity"].asInt();
    replenishment_ = root["replenishment"].asInt();
}


