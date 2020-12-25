#include <Observer.h>
#include <RenderAgent.h>

int main() {
    Observer observer;

    auto windowConfig = observer.launchGame();
    //auto windowConfig = observer.launchGame("Test", -1, 4);
    observer.startGame(windowConfig);
    observer.endGame();

    return 0;
}

