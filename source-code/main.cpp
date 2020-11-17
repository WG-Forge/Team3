#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>

#include "game/Game.h"

using namespace sf;

int main() {
    srand(time(0));

    Game game (std::make_unique<Configuration>(600, 480, 60, "Graph"));
    game.launchGame();
    return 0;
}