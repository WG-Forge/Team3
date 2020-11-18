#include "Game.h"
#include "../drawing/Point.h"
#include "../builder/JSONReader.h"

Game::Game(std::unique_ptr<Configuration> config)
                        : config_(std::unique_ptr<Configuration>(std::move(config)))
                        , window_(std::make_unique<sf::RenderWindow>())
                        , renderer_(std::make_unique<Renderer>(window_.get())) {

    graph_ = std::make_unique<Graph>(1, "map01");
    graph_->addNode(std::make_unique<Node>(1, 2));
    graph_->addNode(std::make_unique<Node>(2, 3));
    graph_->addEdge(std::make_unique<Edge>(1, 5,
                                           graph_->nodes[1].get(), graph_->nodes[2].get()));
    graph_->addEdge(std::make_unique<Edge>(2, 5,
                                           graph_->nodes[1].get(), graph_->nodes[2].get()));
    graph_->addEdge(std::make_unique<Edge>(3, 5,
                                           graph_->nodes[1].get(), graph_->nodes[2].get()));
    graph_->addEdge(std::make_unique<Edge>(4, 5,
                                           graph_->nodes[1].get(), graph_->nodes[2].get()));

    graph_->nodes[1]->setPosition(Point(50, 50));
    graph_->nodes[2]->setPosition(Point(100, 100));
    std::unique_ptr<Graph> graph = JSONReader::readGraph(
            "../graphsJSON/small_graph.json");
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