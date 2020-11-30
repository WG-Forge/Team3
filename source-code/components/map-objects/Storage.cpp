#include "Storage.h"

Storage::Storage(int idx) : Post(idx, "resources/images/storage.png") {}

void Storage::readLayer1(Json::Value root) {
    Post::readLayer1(root);
    armor_ = root["armor"].asInt();
    armor_capacity_ = root["armor_capacity"].asInt();
    replenishment_ = root["replenishment"].asInt();
}



