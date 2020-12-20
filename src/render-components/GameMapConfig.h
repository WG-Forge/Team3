#pragma once

#include <cstdint>

class GameMapConfig {
public:
    int32_t idx;
    int32_t width;
    int32_t height;
    GameMapConfig(int32_t idx, int32_t width, int32_t height);
};
