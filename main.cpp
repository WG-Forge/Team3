#include <Observer.h>
#include <RenderAgent.h>

int main() {
    Observer observer;

    auto windowConfig = observer.launchGame();

    RenderAgent renderAgent(windowConfig);
    auto window = renderAgent.createWindow();

    //temporary
    while (window->isOpen()) {
        sf::Event e;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            renderAgent.getCamera()->moveLeft(renderAgent.getCamera()->getMoveStep());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            renderAgent.getCamera()->moveUp(renderAgent.getCamera()->getMoveStep());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            renderAgent.getCamera()->moveRight(renderAgent.getCamera()->getMoveStep());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            renderAgent.getCamera()->moveDown(renderAgent.getCamera()->getMoveStep());
        }

        while (window->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window->close();
                break;
            }

            if (e.type == sf::Event::MouseWheelMoved) {
                if (e.mouseWheel.delta > 0) {
                    renderAgent.getCamera()->zoomOut(e.mouseWheel.x, e.mouseWheel.y, window.get());
                } else if (e.mouseWheel.delta < 0) {
                    renderAgent.getCamera()->zoomIn(e.mouseWheel.x, e.mouseWheel.y, window.get());
                }
            }
        }
        window->clear(sf::Color::White);
        window->setView(*renderAgent.getCamera()->getView());

        renderAgent.getRenderer().render(observer.getGraph(), observer.getTrains());
        window->display();
    }

    observer.endGame();

    return 0;
}

