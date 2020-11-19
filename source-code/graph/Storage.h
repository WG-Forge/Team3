#ifndef TEAM3_STORAGE_H
#define TEAM3_STORAGE_H


#include <string>

class Storage {
public:
    Storage(int armor, int armorCapacity, const std::string &name, int replenishment);
private:
    int armor_;
    int armor_capacity_;
    std::string name_;
    int replenishment_;
};


#endif //TEAM3_STORAGE_H
