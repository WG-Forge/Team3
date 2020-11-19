#include "Configuration.h"

Configuration::Configuration(int width, int height, int framerateLimit, std::string title, std::string graphPath)
                                        : width(width)
                                        , height(height)
                                        , framerateLimit(framerateLimit)
                                        , title(title)
                                        , graphPath(graphPath) {}
