#include "City.h"

City::City(int idx, int postIdx, int armor, int armorCapacity, int level, const std::string &name, int nextLevelPrice,
           const std::string &playerIdx, int population, int populationCapacity, int product, int productCapacity,
           int trainCooldown)
                                : Node(idx, postIdx)
                                , armor_(armor)
                                , armor_capacity_(armorCapacity)
                                , level_(level)
                                , name_(name)
                                , next_level_price_(nextLevelPrice)
                                , player_idx_(playerIdx)
                                , population_(population)
                                , population_capacity_(populationCapacity)
                                , product_(product)
                                , product_capacity_(productCapacity)
                                , train_cooldown_(trainCooldown) {}
