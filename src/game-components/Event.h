#include <string>

struct Event {
    enum Type {
        TRAIN_COLLISION = 1,
        HIJACKERS_ASSAULT = 2,
        PARASITES_ASSAULT = 3,
        REFUGEES_ARRIVAL = 4,
        RESOURCE_OVERFLOW = 5,
        RESOURCE_LACK = 6,
        GAME_OVER = 100
    };

    enum DataKey {
        TRAIN_COLLISION_KEY = "train",
        HIJACKERS_ASSAULT_KEY = "hijackers_power",
        PARASITES_ASSAULT_KEY = "parasites_power",
        REFUGEES_ARRIVAL_KEY = "refugees_number"
    };

    Type type;
    uint32_t tick;
    std::string data;
};
