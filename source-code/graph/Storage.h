#ifndef TEAM3_STORAGE_H
#define TEAM3_STORAGE_H


#include <string>
#include "Node.h"

class Storage : public Node {
public:
    Storage(int idx, int point_idx, int armor, int armorCapacity, const std::string &name, int replenishment);
private:
    int idx_;
    int point_idx;
    int armor_;
    int armor_capacity_;
    std::string name_;
    int replenishment_;
};


#endif //TEAM3_STORAGE_H
