#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow *window)
                            : window_(window) {}

void Renderer::render(Graph* g) {

    for (auto const& edge : g->edges) {
        Point p1 = Point(edge.second->getFirstNode()->getPosition());
        Point p2 = Point(edge.second->getSecondNode()->getPosition());
        Point upperP1 = rotationCalculator_.calcUpperLineP1(p1, p2, 2);
        Point upperP2 = rotationCalculator_.calcUpperLineP2(p1, p2, 2);
        Point lowerP1 = rotationCalculator_.calcLowerLineP1(p1, p2, 2);
        Point lowerP2 = rotationCalculator_.calcLowerLineP2(p1, p2, 2);

        sf::Vertex line[] =
                {
                        sf::Vertex(sf::Vector2f(upperP1.x, upperP1.y), sf::Color::Red),
                        sf::Vertex(sf::Vector2f(upperP2.x, upperP2.y), sf::Color::Red),
                        sf::Vertex(sf::Vector2f(lowerP1.x, lowerP1.y), sf::Color::Red),
                        sf::Vertex(sf::Vector2f(lowerP2.x, lowerP2.y), sf::Color::Red)
                };

        window_->draw(line, 4, sf::Lines);
    }

    for (auto const& node : g->nodes) {
        sf::Sprite s;
        sf::Texture* texture;
        if (node.second->getPost()) {
            texture = assetManager_.getOrLoadAsset(node.second->getPost()->getAsset());
        } else {
            texture = assetManager_.getOrLoadAsset("resources/images/unknown.png");
        }
        s = sf::Sprite(*texture);
        s.scale((float) NODE_SIZE_ / texture->getSize().x,
                (float) NODE_SIZE_ / texture->getSize().y);
        s.setPosition(node.second->getPosition().x - NODE_SIZE_/2,
                      node.second->getPosition().y - NODE_SIZE_/2);
        window_->draw(s);
    }
}