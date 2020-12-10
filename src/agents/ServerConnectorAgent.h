#pragma once

#include <cstdint>
#include <string_view>
#include <boost/asio.hpp>
#include <Request.h>
#include <Response.h>
#include <defines.h>

//TODO NEWEST: Throw error codes, not exceptions
//TODO Handle exceptions, possibly thrown by
// ServerConnectorAgent::proceedRequest(const Request &request) (if its needed (?))

using namespace boost::asio;

class ServerConnectorAgent {
private:
    io_service io_service_;
    ip::tcp::socket socket_;
    ip::tcp::endpoint endpoint_; //possibly would be deleted in future

public:
    ServerConnectorAgent();
    ~ServerConnectorAgent();

    Response proceedRequest(const Request& request);
};
