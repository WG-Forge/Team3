#include "Game.h"

#include <builder/JSONReader.h>
#include <layout/Layout.h>

#include <utility>

Game::Game(Configuration config)
                        : config_(std::move(config))
                        , window_(std::make_unique<sf::RenderWindow>())
                        , renderer_(window_.get())
                        , camera_(sf::FloatRect(0,0, 1000, 1000)) {
    //graph_ = JSONReader::readGraph(config_.graphPath);
    connection_.login("Boris");
    graph_ = std::move(JSONReader::readLayer0(connection_.getMap(0)));
    JSONReader::readLayer1(connection_.getMap(1), graph_.get());
    JSONReader::readLayer10(connection_.getMap(10), graph_.get());
    connection_.logout();
    //layout::graphLayout(*graph_, 0, 0, config_.width, config_.height);
}

Game& Game::launchGame() {
    window_->create(sf::VideoMode(config_.width, config_.height), config_.title);
    window_->setFramerateLimit(config_.framerateLimit);

    while (window_->isOpen()) {
        sf::Event e;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            camera_.moveLeft(camera_.getMoveStep());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            camera_.moveUp(camera_.getMoveStep());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            camera_.moveRight(camera_.getMoveStep());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            camera_.moveDown(camera_.getMoveStep());
        }

        while (window_->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window_->close();
                break;
            }

            if (e.type == sf::Event::MouseWheelMoved) {
                if (e.mouseWheel.delta > 0) {
                    camera_.zoomOut(e.mouseWheel.x, e.mouseWheel.y, window_.get());
                } else if (e.mouseWheel.delta < 0) {
                    camera_.zoomIn(e.mouseWheel.x, e.mouseWheel.y, window_.get());
                }
            }
        }
        window_->clear(sf::Color::White);
        window_->setView(*camera_.getView());

        renderer_.render(graph_.get());
        window_->display();
    }
    return *this;
}