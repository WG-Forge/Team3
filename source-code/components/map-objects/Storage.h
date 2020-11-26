#ifndef TEAM3_STORAGE_H
#define TEAM3_STORAGE_H


#include <string>
#include "Post.h"

class Storage : public Post {
public:
    explicit Storage(int idx);
    void readLayer1(Json::Value root) override;
private:
    int armor_ = 0;
    int armor_capacity_ = 0;
    int replenishment_ = 0;
};


#endif //TEAM3_STORAGE_H
