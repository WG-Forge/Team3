#ifndef TEAM3_GAME_H
#define TEAM3_GAME_H

#include <time.h>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "components/graph/Graph.h"
#include "drawing/Renderer.h"
#include "game/Configuration.h"
#include "ServerConnection.h"
#include "Camera.h"

class Game {
private:
    Configuration config_;
    std::unique_ptr<sf::RenderWindow> window_;
    std::unique_ptr<Graph> graph_;
    Renderer renderer_;
    ServerConnection connection_;
    Camera camera_;
public:
    Game(Configuration config);
    Game& launchGame();
};



#endif //TEAM3_GAME_H
