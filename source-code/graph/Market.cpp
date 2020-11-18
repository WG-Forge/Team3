#include "Market.h"

Market::Market(const std::string &name, int product, int productCapacity, int replenishment)
                                                                        : name_(name)
                                                                        , product_(product)
                                                                        , product_capacity_(productCapacity)
                                                                        , replenishment_(replenishment) {}
