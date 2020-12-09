#include <Observer.h>

#include <iostream>

//TODO Parse responses, create graph and setup players
void Observer::launchGame() {
    auto loginData = loginAction_(std::string(defines::player_info::PLAYER_NAME.data()),
                                  std::string(defines::player_info::PASSWORD.data()));
    auto layer0 = mapAction_(0);
    auto layer1 = mapAction_(1);
    auto layer10 = mapAction_(10);
}

void Observer::startGame() {

}

void Observer::endGame() {
    auto logoutData = logoutAction_();
}

Response Observer::loginAction_(const std::string& playerName,
                                const std::string& password,
                                const std::string& gameName,
                                int32_t turnsNumber,
                                uint32_t playersNumber) {
    Request request{Request::LOGIN};

    request.data = std::string("{\"name\":\"").append(playerName).append("\"");

    if (!password.empty()) {
        request.data.append(",\"password\":\"").append(password).append("\"");
    }

    if (!gameName.empty()) {
        request.data.append(",\"game\":\"").append(gameName).append("\"");
    }

    if (turnsNumber >= 1) {
        request.data.append(",\"num_turns\":").append(std::to_string(turnsNumber));
    }

    if (playersNumber > 1) {
        request.data.append(",\"num_players\":").append(std::to_string(playersNumber));
    }

    request.data.push_back('}');
    request.dataSize = uint32_t(request.data.size());

    Response response = serverConnectorAgent_.proceedRequest(request);

    return response;
}

Response Observer::logoutAction_() {
    Response response = serverConnectorAgent_.proceedRequest(
            Request{Request::LOGOUT, 0, ""});

    return response;
}

Response Observer::playerAction_() {
    Response response = serverConnectorAgent_.proceedRequest(
            Request{Request::PLAYER, 0, ""});

    return response;
}

Response Observer::mapAction_(uint32_t layerNumber) {
    Request request{Request::MAP};

    request.data = std::string("{\"layer\":").append(std::to_string(layerNumber)).append("}");
    request.dataSize = request.data.size();

    Response response = serverConnectorAgent_.proceedRequest(request);

    return response;
}

Response Observer::moveAction_(int32_t lineIdx, int32_t speed, int32_t trainIdx) {
    Request request{Request::MOVE};

    request.data = std::string("{\"line_idx\":").append(std::to_string(lineIdx)).append(
            ",\"speed\":").append(std::to_string(speed)).append(
                    ",\"train_idx\":").append(std::to_string(trainIdx)).append("}");
    request.dataSize = request.data.size();

    Response response = serverConnectorAgent_.proceedRequest(request);

    return response;
}

//Response Observer::upgradeAction_(const std::vector<Node*>& posts, vector of trains) {}

Response Observer::turnAction_() {
    Response response = serverConnectorAgent_.proceedRequest(
            Request{Request::TURN, 0, ""});

    return response;
}

Response Observer::gamesAction_() {
    Response response = serverConnectorAgent_.proceedRequest(
            Request{Request::GAMES, 0, ""});

    return response;
}
