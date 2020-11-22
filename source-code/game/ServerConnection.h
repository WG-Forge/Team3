#ifndef TEAM3_SERVERCONNECTION_H
#define TEAM3_SERVERCONNECTION_H

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include "utils/HexConverter.h"

using namespace boost::asio;

class ServerConnection {
private:
    const std::string SERVER_ADDRESS_ = "wgforge-srv.wargaming.net";
    const std::string PORT_ = "443";
    io_service service_;
    ip::tcp::endpoint ep_;
    ip::tcp::socket socket_;

    enum Action
    {
        LOGIN = 1,
        LOGOUT = 2,
        MOVE = 3,
        UPGRADE = 4,
        TURN = 5,
        PLAYER = 6,
        GAMES = 7,
        MAP = 10
    };
    enum Result
    {
        OKEY = 0,
        BAD_COMMAND = 1,
        RESOURCE_NOT_FOUND = 2,
        ACCESS_DENIED = 3,
        INAPPROPRIATE_GAME_STATE = 4,
        TIMEOUT = 5,
        INTERNAL_SERVER_ERROR = 500
    };
    struct ActionMessage
    {
        ActionMessage(Action actionCode, size_t dataLength, std::string data);

        Action actionCode;
        size_t dataLength;
        std::string data;

    };

    struct ResponseMessage
    {
        ResponseMessage(Result result, size_t dataLength, std::string data);

        Result result;
        size_t dataLength;
        std::string data;
    };
public:
    ServerConnection();
    std::string login(const std::string& name);
    void logout();
    std::string getMap(int layer);
    ResponseMessage sendActionMessage(const ActionMessage& actionMessage);
};


#endif //TEAM3_SERVERCONNECTION_H
