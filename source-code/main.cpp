#include <time.h>
#include <string>

#include "game/Game.h"

using namespace sf;

int main() {
    srand(time(nullptr));

    Game game (Configuration(
            640,
            480,
            60,
            "Game"));
    game.launchGame();
    return 0;
}