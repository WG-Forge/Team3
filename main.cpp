#include <Observer.h>
#include <RenderAgent.h>

int main() {
    Observer observer;

    auto windowConfig = observer.launchGame();
    observer.startGame(windowConfig);
    observer.endGame();

    return 0;
}

