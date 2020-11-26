#include "Train.h"

Train::Train(int idx)
             : idx_(idx){}

void Train::readLayer1(Json::Value root) {
    player_idx_ = root["player_idx"].asInt();
    position_ = root["position"].asInt();
    speed_ = root["speed"].asInt();
    fuel_ = root["fuel"].asInt();
    fuel_capacity_ = root["fuel_capacity"].asInt();
    goods_ = root["goods"].asInt();
    level_ = root["level"].asInt();
    next_level_price_ = root["next_level_price"].asInt();
}
