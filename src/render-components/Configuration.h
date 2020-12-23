#pragma once

#include <string>

struct Configuration {
    uint32_t width;
    uint32_t height;
    uint32_t framerateLimit;
    std::string title;
    Configuration(uint32_t width = 640, uint32_t height = 480, uint32_t framerateLimit = 60, std::string title = "Game");
};
