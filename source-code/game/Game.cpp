#include "Game.h"

#include <builder/JSONReader.h>
#include <layout/Layout.h>

Game::Game(Configuration config)
                        : config_(config)
                        , window_(std::make_unique<sf::RenderWindow>())
                        , renderer_(window_.get())
                        , camera_(sf::FloatRect(0,0, config_.width, config_.height)) {
    graph_ = JSONReader::readGraph(config_.graphPath);
    layout::graphLayout(*graph_, 0, 0, config_.width, config_.height);
}

Game& Game::launchGame() {
    window_->create(sf::VideoMode(config_.width, config_.height), config_.title);
    window_->setFramerateLimit(config_.framerateLimit);

    while (window_->isOpen()) {
        sf::Event e;
        while (window_->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window_->close();
                break;
            }

            if (e.type == sf::Event::MouseWheelMoved) {
                camera_.zoom(e.mouseWheel.delta);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                camera_.move(-1, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                camera_.move(0, -1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                camera_.move(1, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                camera_.move(0, 1);
            }
        }
        window_->clear(sf::Color::White);
        window_->setView(*camera_.getView());

        renderer_.render(graph_.get());
        window_->display();
    }
    return *this;
}