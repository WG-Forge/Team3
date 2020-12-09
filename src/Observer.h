#pragma once

#include <Player.h>
#include <GraphAgent.h>
#include <ServerConnectorAgent.h>
#include <JSONParser.h>
#include <defines.h>

class Observer {
private:
    //TODO Function that runs through players and setups them
    std::vector<Player> players_; //first element is for our player
    GraphAgent graphAgent_;
    ServerConnectorAgent serverConnectorAgent_;
    JSONParser jsonParser_;

    //TODO Handle exceptions, possibly thrown by Action methods (if its needed (?))
    Response loginAction_(const std::string& playerName,
                          const std::string& password = "",
                          const std::string& gameName = "",
                          int32_t turnsNumber = -1,
                          uint32_t playersNumber = 1);
    Response logoutAction_();
    Response playerAction_();
    Response mapAction_(uint32_t layerNumber);
    Response moveAction_(int32_t lineIdx, int32_t speed, int32_t trainIdx);
//    Response upgradeAction_(const std::vector<Node*>& posts, vector of trains);
    Response turnAction_();
    //TODO Figure out, what crushes program when one calls gamesAction_() after logoutAction_()
    Response gamesAction_();

public:
    void launchGame();
    void startGame();
    void endGame();
};
