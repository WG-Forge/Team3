#ifndef TEAM3_TRAIN_H
#define TEAM3_TRAIN_H

#include <json/json.h>

class Train {
private:
    int idx_ = 0;
    int player_idx_ = 0;
    int position_ = 0;
    int speed_ = 0;
    int fuel_ = 0;
    int fuel_capacity_ = 0;
    int goods_ = 0;
    int level_ = 0;
    int next_level_price_ = 0;

public:
    explicit Train(int idx);
    void readLayer1(Json::Value root);

    int getPosition() const;
};


#endif //TEAM3_TRAIN_H
