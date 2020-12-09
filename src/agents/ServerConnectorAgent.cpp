#include <ServerConnectorAgent.h>

ServerConnectorAgent::ServerConnectorAgent() : socket_(io_service_) {
    ip::tcp::resolver resolver(io_service_);
    auto endpoints = resolver.resolve(defines::server_info::SERVER_HOSTNAME, defines::server_info::PORT);
    endpoint_ = *boost::asio::connect(socket_, endpoints.begin(), endpoints.end());
}

ServerConnectorAgent::~ServerConnectorAgent() {
    socket_.shutdown(ip::tcp::socket::shutdown_both);
    socket_.close();
}

Response ServerConnectorAgent::proceedRequest(const Request &request) {
    uint32_t actionCode = request.actionCode;
    uint32_t requestDataSize = request.dataSize;
    std::string requestData = request.data;
    Response response;

    std::vector<unsigned char> byteArray(2 * sizeof(uint32_t) + requestData.size());

    {
        uint32_t i = 0;

        for (; i < sizeof(uint32_t); ++i) {
            byteArray[i] = (actionCode >> (8 * i)) & 0xFF;
        }

        for (; i < 2 * sizeof(uint32_t); ++i) {
            byteArray[i] = (requestDataSize >> (8 * i)) & 0xFF;
        }

        for (uint32_t j = 0; j < requestData.size(); ++i, ++j) {
            byteArray[i] = requestData[j];
        }
    }

    boost::asio::write(socket_, buffer(byteArray),
                       boost::asio::transfer_all());

    byteArray.resize(2 * sizeof(uint32_t));

    boost::asio::read(
            socket_, buffer(byteArray),
            boost::asio::transfer_exactly(byteArray.size()));

    {
        uint32_t resultCode = 0;
        uint32_t dataSize = 0;

        for (uint32_t i = 0; i < sizeof(uint32_t); ++i) {
            resultCode |= byteArray[i] << (8 * i);
            dataSize |= byteArray[i + sizeof(uint32_t)] << (8 * i);
        }

        response.resultCode = static_cast<Response::Result>(resultCode);
        response.dataSize = dataSize;
    }

    byteArray.resize(response.dataSize);

    boost::asio::read(
            socket_, buffer(byteArray),
            boost::asio::transfer_exactly(byteArray.size()));

    for (uint32_t i = 0; i < response.dataSize; ++i) {
        response.data.push_back(byteArray[i]);
    }

    return response;
}
