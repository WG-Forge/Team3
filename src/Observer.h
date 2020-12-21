#pragma once

#include <defines.h>
#include <Player.h>
#include <Edge.h>
#include <JSONReader.h>
#include <GameMapConfig.h>
#include <GraphAgent.h>
#include <ServerConnectorAgent.h>
#include <TrainsAgent.h>
#include <MoveAgent.h>
#include <RenderAgent.h>

#include <chrono>

//TODO NEWEST: Throw error codes, not exceptions
//TODO Handle exceptions, possibly thrown by Action methods (if its needed (?))

//TODO Function that runs through players and setups them
//TODO Figure out, what crushes program when one calls gamesAction_() after logoutAction_()

class Observer {
private:
    const int MS_PER_UPDATE = 700;
    std::string currentTurnLayer1;
    std::vector<Player> players_; //first element is for our player
    GraphAgent graphAgent_;
    TrainsAgent trainsAgent_;
    ServerConnectorAgent serverConnectorAgent_;
    MoveAgent moveAgent_;
    JSONReader jsonParser_;
    uint32_t hometownIdx;

    Response loginAction_(const std::string& playerName,
                          const std::string& password = "",
                          const std::string& gameName = "",
                          int32_t turnsNumber = -1,
                          uint32_t playersNumber = 1);
    Response logoutAction_();
    Response playerAction_();
    Response mapAction_(uint32_t layerNumber);
    Response moveAction_(int32_t lineIdx, int32_t speed, int32_t trainIdx);
    Response turnAction_();
    Response gamesAction_();

    void preserveLoginData_(JSON_OBJECT_AS_MAP& root);
    void preserveLayer0Data_(JSON_OBJECT_AS_MAP& root);
    void preserveLayer1Data_(JSON_OBJECT_AS_MAP& root);
    GameMapConfig preserveLayer10Data_(JSON_OBJECT_AS_MAP& root);

    bool update();
    void moveTrains();

public:
    GameMapConfig launchGame();
    void startGame(GameMapConfig config);
    void endGame();
};
