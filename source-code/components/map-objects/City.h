#ifndef TEAM3_CITY_H
#define TEAM3_CITY_H


#include <string>
#include "Post.h"

class City : public Post {
public:
    explicit City(int idx);
    void readLayer1(Json::Value root) override;

private:
    int armor_;
    int armor_capacity_;
    int level_;
    int next_level_price_;
    std::string player_idx_;
    int population_;
    int population_capacity_;
    int product_;
    int product_capacity_;
    int train_cooldown_;
};


#endif //TEAM3_CITY_H
