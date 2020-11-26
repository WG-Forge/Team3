#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>

#include "game/Game.h"

using namespace sf;

int main() {
    srand(time(0));

    Game game (Configuration(
            640,
            480,
            60,
            "Graph",
            "../../graphsJSON/big_graph.json")
            );
    game.launchGame();
    return 0;
}