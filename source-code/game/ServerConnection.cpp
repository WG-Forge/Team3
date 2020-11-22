#include "ServerConnection.h"

ServerConnection::ServerConnection()
                            : socket_(service_) {
    ip::tcp::resolver resolver(service_);
    ip::tcp::resolver::query query(SERVER_ADDRESS_, PORT_);
    ip::tcp::resolver::iterator iter = resolver.resolve(query);
    ep_ = *iter;
    //ep_ = ip::tcp::endpoint(ip::address::from_string("127.0.0.1"), 65432);
    socket_.connect(ep_);
}

std::string ServerConnection::login(const std::string& name) {
    std::string data = R"({"name":"Boris"})";
    ServerConnection::ResponseMessage response =
            sendActionMessage(ActionMessage (LOGIN, data.length(), data));
    if (response.result == OKEY) {
        return response.data;
    }
    throw "Bad response";
}

void ServerConnection::logout() {
    ServerConnection::ResponseMessage response =
            sendActionMessage(ActionMessage (LOGOUT, 0, ""));
    if (!response.result == OKEY) {
        throw "Bad response";
    }
}


std::string ServerConnection::getMap(int layer) {
    std::string data = R"({"layer":)" + std::to_string(layer) + "}";
    ServerConnection::ResponseMessage response =
            sendActionMessage(ActionMessage (MAP, data.length(), data));
    if (response.result == OKEY) {
        return response.data;
    }
    std::cout << response.data;
    return "";
}


ServerConnection::ResponseMessage ServerConnection::sendActionMessage(const ActionMessage& actionMessage) {
    std::string request;
    request += BinaryConverter::intToHex(actionMessage.actionCode);
    request += BinaryConverter::intToHex(actionMessage.dataLength);
    request += BinaryConverter::stringToHex(actionMessage.data);
    socket_.send(buffer(request));

    char responseCode[4];
    socket_.receive(buffer(responseCode, 4));
    int code = BinaryConverter::hexToInt(responseCode);

    char responseSize[4];
    socket_.receive(buffer(responseSize, 4));
    int size = BinaryConverter::hexToInt(responseSize);

    char responseData[size];
    boost::asio::read(
            socket_, boost::asio::buffer(responseData, size),
            boost::asio::transfer_all());
    std::string data = BinaryConverter::hexToString(responseData);
    data = data.substr(0, size);
    return ServerConnection::ResponseMessage(Result(code), size, data);
}

ServerConnection::ActionMessage::ActionMessage(Action actionCode,
                                               size_t dataLength,
                                               std::string data)
        : actionCode(actionCode), dataLength(dataLength), data(data) {}

ServerConnection::ResponseMessage::ResponseMessage(Result result,
                                                 size_t dataLength,
                                                 std::string data)
        : result(result), dataLength(dataLength), data(data) {}