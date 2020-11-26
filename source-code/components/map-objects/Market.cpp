#include "Market.h"


Market::Market(int idx) : Post(idx) {
    type = Type::MARKET;
}

void Market::readLayer1(Json::Value root) {
    Post::readLayer1(root);
    product_ = root["product"].asInt();
    product_capacity_ = root["product_capacity"].asInt();
    replenishment_ = root["replenishment"].asInt();
}


