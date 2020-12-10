#include <string>

#include "game/Game.h"

using namespace sf;

int main() {
    Game game (Configuration(
            640,
            480,
            60,
            "Game"));
    game.launchGame();
    return 0;
}