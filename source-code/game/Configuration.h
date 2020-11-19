#ifndef TEAM3_CONFIGURATION_H
#define TEAM3_CONFIGURATION_H

#include <string>

struct Configuration {
    int width;
    int height;
    int framerateLimit;
    std::string title;
    std::string graphPath;
    Configuration(int width, int height, int framerateLimit, std::string title, std::string graphPath);
};


#endif //TEAM3_CONFIGURATION_H
