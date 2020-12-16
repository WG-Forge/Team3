#include <Observer.h>

//TODO Remove constructor arguments in agregated classes were possible (after testing different responses from server)
//TODO Add parsing window size to preserveLayer10Data_(JSON_ROOT_AS_MAP& root)
//TODO Add parsing ratings to preserveLayer1Data_(JSON_ROOT_AS_MAP& root)

GameMapConfig Observer::launchGame() {
    auto loginData = loginAction_(std::string(defines::player_info::PLAYER_NAME.data()),
                                  std::string(defines::player_info::PASSWORD.data()));
    auto layer0 = mapAction_(0);
    auto layer1 = mapAction_(1);
    auto layer10 = mapAction_(10);

    auto readLoginData = jsonParser_.read(loginData.data);
    auto readLayer0 = jsonParser_.read(layer0.data);
    auto readLayer1 = jsonParser_.read(layer1.data);
    auto readLayer10 = jsonParser_.read(layer10.data);

    preserveLoginData_(readLoginData);
    preserveLayer0Data_(readLayer0);
    preserveLayer1Data_(readLayer1);
    auto windowConfig = preserveLayer10Data_(readLayer10);

    moveAgent_.move(graphAgent_.getGraph(), trainsAgent_.getAllTrains()[0]);

    return windowConfig;
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

    request.data = std::string(R"({"name":")").append(playerName).append("\"");

    if (!password.empty()) {
        request.data.append(R"(,"password":")").append(password).append("\"");
    }

    if (!gameName.empty()) {
        request.data.append(R"(,"game":")").append(gameName).append("\"");
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

//Response Observer::upgradeAction_(const std::vector<Node*>& posts, container with trains) {}

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

void Observer::preserveLoginData_(JSON_OBJECT_AS_MAP& root) {
    players_.emplace_back(root["name"].asCString(), root["idx"].asCString(),
                              root["rating"].asUInt(), true);
}

void Observer::preserveLayer0Data_(JSON_OBJECT_AS_MAP& root) {
    int32_t counter = 0;

    for (const auto& point : root["points"]) {
        ++counter;

        int32_t pointIdx = point["idx"].asInt();
        int32_t postIdx = point["post_idx"].asInt();

        if (postIdx == 0) {
            graphAgent_.pointIdxCompression_[pointIdx] =
                    graphAgent_.graph_.size();
            graphAgent_.graph_.push_back(new Node(pointIdx, postIdx));
        } else {
            continue;
        }
    }

    for (const auto& line : root["lines"]) {
        graphAgent_.edgeCreationHelpers_.push_back(
                {line["idx"].asInt(), line["length"].asUInt(),
                 line["points"][0].asInt(), line["points"][1].asInt()}
                );
    }

    //root["name"] for name of layer (?do we need it?)
    //root["idx"] for index of layer (?do we need it?)
}

void Observer::preserveLayer1Data_(JSON_OBJECT_AS_MAP& root) {
    Hometown* hometown = nullptr;

    for (const auto& post : root["posts"]) {
        int32_t pointIdx = post["point_idx"].asInt();
        int32_t postIdx = post["idx"].asInt();
        std::string playerIdx;

        static bool isMine = false;

        graphAgent_.pointIdxCompression_[pointIdx] =
                graphAgent_.graph_.size();

        switch (post["type"].asUInt()) {
            case Town::TYPE :
                if (post["player_idx"].type() == JSON_VALUE_TYPE::stringValue) {
                    playerIdx = post["player_idx"].asCString();
                }

                if (!isMine) {
                    if (playerIdx == players_[0].getIdx()) {
                        isMine = true;

                        graphAgent_.graph_.push_back(new Hometown(pointIdx, postIdx,
                                                              playerIdx,
                                                              post["next_level_price"].asUInt(),
                                                              post["population_capacity"].asUInt(),
                                                              post["product_capacity"].asUInt(),
                                                              post["armor_capacity"].asUInt(),
                                                              post["level"].asUInt(),
                                                              post["population"].asUInt(),
                                                              post["product"].asUInt(),
                                                              post["armor"].asUInt(),
                                                              post["name"].asCString(),
                                                              isMine));
                        hometown = static_cast<Hometown*>(graphAgent_.graph_[graphAgent_.graph_.size() - 1]);

                        break;
                    }
                }

                graphAgent_.graph_.push_back(new Town(pointIdx, postIdx,
                                                      playerIdx,
                                                      post["next_level_price"].asUInt(),
                                                      post["population_capacity"].asUInt(),
                                                      post["product_capacity"].asUInt(),
                                                      post["armor_capacity"].asUInt(),
                                                      post["level"].asUInt(),
                                                      post["population"].asUInt(),
                                                      post["product"].asUInt(),
                                                      post["armor"].asUInt(),
                                                      post["name"].asCString(),
                                                      isMine));

                break;

            case Market::TYPE :
                graphAgent_.graph_.push_back(new Market(pointIdx, postIdx,
                                                        post["product_capacity"].asUInt(),
                                                        post["replenishment"].asUInt(),
                                                        post["product"].asUInt(),
                                                        post["name"].asCString()));

                break;

            case Storage::TYPE :
                graphAgent_.graph_.push_back(new Storage(pointIdx, postIdx,
                                                        post["armor_capacity"].asUInt(),
                                                        post["replenishment"].asUInt(),
                                                        post["armor"].asUInt(),
                                                        post["name"].asCString()));

                break;
        }
    }

    for (const auto& edgeCreationHelper : graphAgent_.edgeCreationHelpers_) {
        int32_t firstPointIdx = graphAgent_.pointIdxCompression_.at(edgeCreationHelper.firstPointIdx);
        int32_t secondPointIdx = graphAgent_.pointIdxCompression_.at(edgeCreationHelper.secondPointIdx);

        Edge* edge = new Edge(edgeCreationHelper.lineIdx, edgeCreationHelper.length,
                  graphAgent_.graph_[firstPointIdx],
                  graphAgent_.graph_[secondPointIdx]);

        graphAgent_.mapEdge(edge);
        graphAgent_.graph_[firstPointIdx]->addNeighbor(edge);
        graphAgent_.graph_[secondPointIdx]->addNeighbor(edge);
    }

    for (auto& train : root["trains"]) {
        int32_t lineIdx = train["line_idx"].asInt();
        auto playerIdx = train["player_idx"].asCString();

        Train* addTrain = new Train(train["idx"].asInt(),
                    lineIdx,
                    train["position"].asUInt(),
                    train["speed"].asInt(),
                    train["next_level_price"].asUInt(),
                    train["goods_capacity"].asUInt(),
                    train["fuel_capacity"].asUInt(),
                    train["fuel_consumption"].asUInt(),
                    train["fuel"].asUInt(),
                    train["goods"].asUInt(),
                    Train::GoodsType::NOTHING,
                    train["level"].asUInt(),
                    playerIdx,
                    true);

        trainsAgent_.addTrain(addTrain);
        addTrain->setAttachedEdge(graphAgent_.findEdge(lineIdx));

        if (playerIdx == hometown->getPlayerIdx()) {
            hometown->addTrain(addTrain);
        }
    }
}

GameMapConfig Observer::preserveLayer10Data_(JSON_OBJECT_AS_MAP& root) {
    for (const auto& coordinates : root["coordinates"]) {
        uint32_t pointIndex = graphAgent_.pointIdxCompression_.at(coordinates["idx"].asInt());

        graphAgent_.graph_[pointIndex]->setCoordinates(
                coordinates["x"].asUInt(), coordinates["y"].asUInt());
    }

    int32_t idx = root["idx"].asInt();
    uint32_t width = root["size"][0].asUInt();
    uint32_t height = root["size"][1].asUInt();

    return GameMapConfig(idx, width, height);
}

std::vector<Node*>& Observer::getGraph() {
    return graphAgent_.getGraph();
}

std::vector<Train*> &Observer::getTrains() {
    return trainsAgent_.getAllTrains();
}
