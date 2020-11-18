#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>

#include "game/Game.h"

using namespace sf;

int main() {
    srand(time(0));

    Game game (std::make_unique<Configuration>(1920, 1080, 60, "Graph"));
    game.launchGame();
    return 0;
}