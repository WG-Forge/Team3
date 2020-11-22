//
// Created by liza on 11/22/20.
//

#include "Train.h"

Train::Train(int idx, int line_idx, int player_idx, int position, int speed, int fuel, int fuel_capacity, int goods,
             int level, int next_level_price)
             : idx_(idx)
             , line_idx_(line_idx)
             , player_idx_(player_idx)
             , position_(position)
             , speed_(speed)
             , fuel_(fuel)
             , fuel_capacity_(fuel_capacity)
             , goods_(goods)
             , level_(level)
             , next_level_price_(next_level_price){}