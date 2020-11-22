//
// Created by liza on 11/22/20.
//

#ifndef TEAM3_TRAIN_H
#define TEAM3_TRAIN_H


#include "Edge.h"

class Train {
private:
    int idx_;
    int line_idx_;
    int player_idx_;
    int position_;
    int speed_;
    int fuel_;
    int fuel_capacity_;
    int goods_;
    int level_;
    int next_level_price_{};

public:
    Train(int idx, int line_idx, int player_idx,
                                int position,
                                int speed,
                                int fuel,
                                int fuel_capacity,
                                int goods,
                                int level,
                                int next_level_price);

};


#endif //TEAM3_TRAIN_H
