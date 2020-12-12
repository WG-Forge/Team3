#pragma once

#include <cstdint>

struct Point {
    uint32_t x;
    uint32_t y;

    Point() : x(0), y(0) {}
    Point(uint32_t x, uint32_t y) : x(x), y(y) {}
};
