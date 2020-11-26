#include "Storage.h"

Storage::Storage(int idx) : Post(idx) {
    type = Type::STORAGE;
}

void Storage::readLayer1(Json::Value root) {
    Post::readLayer1(root);
    armor_ = root["armor"].asInt();
    armor_capacity_ = root["armor_capacity"].asInt();
    replenishment_ = root["replenishment"].asInt();
}



