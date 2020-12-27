#include <Observer.h>
#include <RenderAgent.h>

int main() {
    Observer observer;

    auto windowConfig = observer.launchGame(defines::player_info::PLAYER_NAME.data(),
                                            defines::player_info::PASSWORD.data(), "", 500, 1);
    observer.startGame(windowConfig);
    observer.endGame();

    return 0;
}

