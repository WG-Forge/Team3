#ifndef TEAM3_GAME_H
#define TEAM3_GAME_H

#include <time.h>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "graph/Graph.h"
#include "drawing/Renderer.h"
#include "game/Configuration.h"
#include "ServerConnection.h"

class Game {
private:
    std::unique_ptr<Configuration> config_;
    std::unique_ptr<sf::RenderWindow> window_;
    std::unique_ptr<Graph> graph_;
    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<sf::View> camera_;
    std::unique_ptr<ServerConnection> connection_;
public:
    Game(std::unique_ptr<Configuration> config);
    Game& launchGame();
};



#endif //TEAM3_GAME_H
