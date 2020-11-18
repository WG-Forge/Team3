#ifndef TEAM3_CITY_H
#define TEAM3_CITY_H


#include <string>
#include "Node.h"

class City : public Node {
public:
    City(int idx, int postIdx, int armor, int armorCapacity, int level, const std::string &name, int nextLevelPrice,
         const std::string &playerIdx, int population, int populationCapacity, int product, int productCapacity,
         int trainCooldown);

private:
    int armor_;
    int armor_capacity_;
    int level_;
    std::string name_;
    int next_level_price_;
    std::string player_idx_;
    int population_;
    int population_capacity_;
    int product_;
    int product_capacity_;
    int train_cooldown_;
};


#endif //TEAM3_CITY_H
