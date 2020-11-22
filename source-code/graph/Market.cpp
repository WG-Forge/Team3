#include "Market.h"

Market::Market(int idx, int point_idx,const std::string &name, int product, int productCapacity, int replenishment)
                                                                        : Node(idx, point_idx), idx_(idx)
                                                                        , point_idx_(point_idx_)
                                                                        , name_(name)
                                                                        , product_(product)
                                                                        , product_capacity_(productCapacity)
                                                                        , replenishment_(replenishment) {}

