#include "Storage.h"

Storage::Storage(int armor, int armorCapacity, const std::string &name, int replenishment)
                                                                : armor_(armor)
                                                                , armor_capacity_(armorCapacity)
                                                                , name_(name)
                                                                , replenishment_(replenishment) {}
