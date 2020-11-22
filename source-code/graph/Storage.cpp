#include "Storage.h"

Storage::Storage(int idx, int point_idx, int armor, int armorCapacity, const std::string &name, int replenishment)
                                                                : Node(idx, point_idx)
                                                                , idx_(idx)
                                                                , point_idx(point_idx)
                                                                , armor_(armor)
                                                                , armor_capacity_(armorCapacity)
                                                                , name_(name)
                                                                , replenishment_(replenishment) {}
