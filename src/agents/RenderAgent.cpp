#include <RenderAgent.h>

RenderAgent::RenderAgent(GameMapConfig map)
        : window_(std::make_unique<sf::RenderWindow>())
        , renderer_(window_.get()) {
    camera_ = std::make_unique<Camera>(sf::FloatRect(0,0, map.width, map.height));
}

RenderAgent::RenderAgent(Configuration config, GameMapConfig map)
        : config_(std::move(config))
        , window_(std::make_unique<sf::RenderWindow>())
        , renderer_(window_.get()) {
    camera_ = std::make_unique<Camera>(sf::FloatRect(0,0, map.width, map.height));
}

Renderer& RenderAgent::getRenderer() {
    return renderer_;
}

std::unique_ptr<Camera>& RenderAgent::getCamera() {
    return camera_;
}

sf::RenderWindow* RenderAgent::createWindow() {
    window_->create(sf::VideoMode(config_.width, config_.height), config_.title);
    window_->setFramerateLimit(config_.framerateLimit);

    return window_.get();
}
