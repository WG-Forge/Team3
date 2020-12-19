#include <Observer.h>

//TODO Remove constructor arguments in agregated classes were possible (after testing different responses from server)
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

    return windowConfig;
}

void Observer::startGame(GameMapConfig config) {
    RenderAgent renderAgent(config);
    auto window = renderAgent.createWindow();

    while (window->isOpen()) {
        sf::Event e;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            renderAgent.getCamera()->moveLeft(renderAgent.getCamera()->getMoveStep());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            renderAgent.getCamera()->moveUp(renderAgent.getCamera()->getMoveStep());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            renderAgent.getCamera()->moveRight(renderAgent.getCamera()->getMoveStep());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            renderAgent.getCamera()->moveDown(renderAgent.getCamera()->getMoveStep());
        }

        while (window->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window->close();
                break;
            }

            if (e.type == sf::Event::MouseWheelMoved) {
                if (e.mouseWheel.delta > 0) {
                    renderAgent.getCamera()->zoomOut(e.mouseWheel.x, e.mouseWheel.y, window.get());
                } else if (e.mouseWheel.delta < 0) {
                    renderAgent.getCamera()->zoomIn(e.mouseWheel.x, e.mouseWheel.y, window.get());
                }
            }
        }
        window->clear(sf::Color::White);
        window->setView(*renderAgent.getCamera()->getView());

        renderAgent.getRenderer().render(graphAgent_.graph_, trainsAgent_.trains_);
        window->display();
    }
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
    Town* town = nullptr;
    Hometown* hometown = nullptr;
    Market* market = nullptr;
    Storage* storage = nullptr;

    auto& trains = trainsAgent_.getAllTrains();

    for (const auto& readPost : root["posts"]) {
        int32_t pointIdx = readPost["point_idx"].asInt();
        int32_t postIdx = readPost["idx"].asInt();
        std::string playerIdx;

        bool exists = false;
        auto index = graphAgent_.pointIdxCompression_.find(pointIdx);

        if (index != graphAgent_.pointIdxCompression_.end()) {
            exists = true;
        } else {
            graphAgent_.pointIdxCompression_[pointIdx] =
                    graphAgent_.graph_.size();
        }

        switch (readPost["type"].asUInt()) {
            case Town::TYPE :
                if (readPost["player_idx"].type() == JSON_VALUE_TYPE::stringValue) {
                    playerIdx = readPost["player_idx"].asCString();
                }

                if (playerIdx == players_[0].getIdx()) {
                    if (exists) {
                        hometown = static_cast<Hometown*>(graphAgent_.graph_[index->second]);

                        hometown->setProduct(readPost["product"].asUInt());
                        hometown->setArmor(readPost["armor"].asUInt());
                        hometown->setPopulation(readPost["population"].asUInt());
                    } else {
                        graphAgent_.graph_.push_back(new Hometown(pointIdx, postIdx,
                                                                  playerIdx,
                                                                  readPost["next_level_price"].asUInt(),
                                                                  readPost["population_capacity"].asUInt(),
                                                                  readPost["product_capacity"].asUInt(),
                                                                  readPost["armor_capacity"].asUInt(),
                                                                  readPost["level"].asUInt(),
                                                                  readPost["population"].asUInt(),
                                                                  readPost["product"].asUInt(),
                                                                  readPost["armor"].asUInt(),
                                                                  readPost["name"].asCString(),
                                                                  true));
                        hometown = static_cast<Hometown*>(graphAgent_.graph_[graphAgent_.graph_.size() - 1]);

                        break;
                    }
                }

                if (exists) {
                    town = static_cast<Town*>(graphAgent_.graph_[index->second]);

                    town->setProduct(readPost["product"].asUInt());
                    town->setArmor(readPost["armor"].asUInt());
                    town->setPopulation(readPost["population"].asUInt());
                } else {
                    graphAgent_.graph_.push_back(new Town(pointIdx, postIdx,
                                                          playerIdx,
                                                          readPost["next_level_price"].asUInt(),
                                                          readPost["population_capacity"].asUInt(),
                                                          readPost["product_capacity"].asUInt(),
                                                          readPost["armor_capacity"].asUInt(),
                                                          readPost["level"].asUInt(),
                                                          readPost["population"].asUInt(),
                                                          readPost["product"].asUInt(),
                                                          readPost["armor"].asUInt(),
                                                          readPost["name"].asCString(),
                                                          false));

                    break;
                }

            case Market::TYPE :
                if (exists) {
                    market = static_cast<Market*>(graphAgent_.graph_[index->second]);

                    market->setProduct(readPost["product"].asUInt());
                } else {
                    graphAgent_.graph_.push_back(new Market(pointIdx, postIdx,
                                                            readPost["product_capacity"].asUInt(),
                                                            readPost["replenishment"].asUInt(),
                                                            readPost["product"].asUInt(),
                                                            readPost["name"].asCString()));

                    break;
                }

            case Storage::TYPE :
                if (exists) {
                    storage = static_cast<Storage*>(graphAgent_.graph_[index->second]);

                    storage->setArmor(readPost["armor"].asUInt());
                } else {
                    graphAgent_.graph_.push_back(new Storage(pointIdx, postIdx,
                                                             readPost["armor_capacity"].asUInt(),
                                                             readPost["replenishment"].asUInt(),
                                                             readPost["armor"].asUInt(),
                                                             readPost["name"].asCString()));

                    break;
                }
        }
    }

    for (const auto &edgeCreationHelper : graphAgent_.edgeCreationHelpers_) {
        int32_t firstPointIdx = graphAgent_.pointIdxCompression_.at(edgeCreationHelper.firstPointIdx);
        int32_t secondPointIdx = graphAgent_.pointIdxCompression_.at(edgeCreationHelper.secondPointIdx);

        Edge *edge = new Edge(edgeCreationHelper.lineIdx, edgeCreationHelper.length,
                              graphAgent_.graph_[firstPointIdx],
                              graphAgent_.graph_[secondPointIdx]);

        graphAgent_.mapEdge(edge);
        graphAgent_.graph_[firstPointIdx]->addNeighbor(edge);
        graphAgent_.graph_[secondPointIdx]->addNeighbor(edge);
    }

    graphAgent_.edgeCreationHelpers_.clear();

    for (auto& readTrain : root["trains"]) {
        int32_t lineIdx = readTrain["line_idx"].asInt();
        int32_t trainIdx = readTrain["idx"].asInt();
        auto playerIdx = readTrain["player_idx"].asCString();

        auto index = trainsAgent_.trainIdxCompression_.find(trainIdx);

        if (index != trainsAgent_.trainIdxCompression_.end()) {
            Train* train = trainsAgent_.trains_[index->second];

            train->setSpeed(readTrain["speed"].asInt());
            train->setPosition(readTrain["position"].asUInt());
            train->setFuel(readTrain["fuel"].asUInt());
            train->setAttachedEdge(graphAgent_.findEdge(lineIdx));
        } else {
            trainsAgent_.trainIdxCompression_[trainIdx] = trainsAgent_.trains_.size();

            Train* addTrain = new Train(trainIdx,
                                        lineIdx,
                                        readTrain["position"].asUInt(),
                                        readTrain["speed"].asInt(),
                                        readTrain["next_level_price"].asUInt(),
                                        readTrain["goods_capacity"].asUInt(),
                                        readTrain["fuel_capacity"].asUInt(),
                                        readTrain["fuel_consumption"].asUInt(),
                                        readTrain["fuel"].asUInt(),
                                        readTrain["goods"].asUInt(),
                                        Train::GoodsType::NOTHING,
                                        readTrain["level"].asUInt(),
                                        playerIdx,
                                        true);

            trainsAgent_.addTrain(addTrain);
            addTrain->setAttachedEdge(graphAgent_.findEdge(lineIdx));

            if (playerIdx == hometown->getPlayerIdx()) {
                hometown->addTrain(addTrain);
            }
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
