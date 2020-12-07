#pragma once

#include <cstdint>
#include <string_view>
#include <boost/asio.hpp>
#include <Request.h>
#include <Response.h>

using namespace boost::asio;

class ServerConnectorAgent {
public:
    constexpr static std::string_view SERVER_HOSTNAME = "wgforge-srv.wargaming.net";
    constexpr static std::string_view PORT = "443";

private:
    io_service io_service_;
    ip::tcp::socket socket_;
    ip::tcp::endpoint endpoint_; //possibly would be deleted in future

public:
    ServerConnectorAgent();
    ~ServerConnectorAgent();

    Response proceedRequest(const Request& request);
};
