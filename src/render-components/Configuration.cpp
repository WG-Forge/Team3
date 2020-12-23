#include <Configuration.h>

Configuration::Configuration(uint32_t width, uint32_t height, uint32_t framerateLimit, std::string title)
        : width(width)
        , height(height)
        , framerateLimit(framerateLimit)
        , title(title) {}
