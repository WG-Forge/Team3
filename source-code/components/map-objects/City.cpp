#include "City.h"

City::City(int idx) : Post(idx) {}

void City::readLayer1(Json::Value root) {
    Post::readLayer1(root);
    armor_ = root["armor"].asInt();
    armor_capacity_ = root["armor_capacity"].asInt();
    level_ = root["level"].asInt();
    next_level_price_ = root["next_level_price"].asInt();
    player_idx_ = root["player_idx"].asString();
    population_ = root["population"].asInt();
    population_capacity_ = root["population_capacity"].asInt();
    product_ = root["product"].asInt();
    product_capacity_ = root["product_capacity"].asInt();
    train_cooldown_ = root["train_cooldown"].asInt();
}
