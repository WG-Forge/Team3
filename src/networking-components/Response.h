#pragma once

#include <string>

struct Response {
    enum Result {
        OKAY = 0,
        BAD_COMMAND = 1,
        RESOURCE_NOT_FOUND = 2,
        ACCESS_DENIED = 3,
        INAPPROPRIATE_GAME_STATE = 4,
        TIMEOUT = 5,
        INTERNAL_SERVER_ERROR = 500
    };

    Result resultCode;
    uint32_t dataSize; //because byte manipulations are provided for 4 byte integers
    std::string data;
};
