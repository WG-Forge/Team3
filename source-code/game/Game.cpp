#include "Game.h"
#include "../drawing/Point.h"

Game::Game(std::unique_ptr<Configuration> config)
                        : config_(std::unique_ptr<Configuration>(std::move(config)))
                        , window_(std::make_unique<sf::RenderWindow>())
                        , renderer_(std::make_unique<Renderer>(window_.get())) {

    graph_ = std::make_unique<Graph>(1, "map01");
    graph_->addNode(std::make_unique<Node>(1, 2));
    graph_->addNode(std::make_unique<Node>(2, 3));
    graph_->addEdge(std::make_unique<Edge>(1, 5,
                                           graph_->nodes[0].get(), graph_->nodes[1].get()));
    graph_->addEdge(std::make_unique<Edge>(2, 5,
                                           graph_->nodes[0].get(), graph_->nodes[1].get()));
    graph_->addEdge(std::make_unique<Edge>(3, 5,
                                           graph_->nodes[0].get(), graph_->nodes[1].get()));
    graph_->addEdge(std::make_unique<Edge>(4, 5,
                                           graph_->nodes[0].get(), graph_->nodes[1].get()));

    graph_->nodes[0]->setPosition(std::make_unique<Point>(50, 50));
    graph_->nodes[1]->setPosition(std::make_unique<Point>(100, 100));
    //std::unique_ptr<Graph> graph = JSONReader::readGraph(fileName.toStdString());

}

Game& Game::launchGame() {
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
        renderer_->render(graph_.get());
        window_->display();
    }
    return *this;
}