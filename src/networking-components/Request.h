#pragma once

#include <string>

struct Request {
    enum Action {
        LOGIN = 1,
        LOGOUT = 2,
        MOVE = 3,
        UPGRADE = 4,
        TURN = 5,
        PLAYER = 6,
        GAMES = 7,
        MAP = 10
    };

    Action actionCode;
    uint32_t dataSize; //because byte manipulations are provided for 4 byte integers
    std::string data;
};
