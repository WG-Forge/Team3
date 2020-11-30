#ifndef TEAM3_CONFIGURATION_H
#define TEAM3_CONFIGURATION_H

#include <string>

struct Configuration {
    int width;
    int height;
    int framerateLimit;
    std::string title;
    Configuration(int width, int height, int framerateLimit, std::string title);
};


#endif //TEAM3_CONFIGURATION_H
