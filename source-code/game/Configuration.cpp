#include "Configuration.h"

Configuration::Configuration(int width, int height, int framerateLimit, std::string title)
                                        : width(width)
                                        , height(height)
                                        , framerateLimit(framerateLimit)
                                        , title(title) {}
