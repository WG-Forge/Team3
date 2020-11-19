#include "Game.h"

#include <builder/JSONReader.h>
#include <layout/Layout.h>

Game::Game(std::unique_ptr<Configuration> config)
                        : config_(std::unique_ptr<Configuration>(std::move(config)))
                        , window_(std::make_unique<sf::RenderWindow>())
                        , renderer_(std::make_unique<Renderer>(window_.get())) {
    graph_ = JSONReader::readGraph(config_->graphPath);
    layout::graphLayout(*graph_, 0, 0, config_->width, config_->height);
}

Game& Game::launchGame() {
    camera_ = std::make_unique<sf::View>(sf::FloatRect(0,0, config_->width, config_->height));
    camera_->zoom(1);
    window_->create(sf::VideoMode(config_->width, config_->height), config_->title);
    window_->setFramerateLimit(config_->framerateLimit);

    while (window_->isOpen()) {
        sf::Event e;
        while (window_->pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window_->close();
                break;
            }
        }
        window_->clear(sf::Color::White);
        window_->setView(*camera_);

        renderer_->render(graph_.get());
        window_->display();
    }
    return *this;
}