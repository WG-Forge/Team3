#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow *window)
                            : window_(window)
                            , rotationCalculator_(std::make_unique<RotationCalculator>()) {}

void Renderer::render(Graph* g) {

    for (auto const& edge : g->edges) {
        Point p1 = Point(edge.second->getFirstNode()->getPosition());
        Point p2 = Point(edge.second->getSecondNode()->getPosition());
        Point upperP1 = rotationCalculator_->calcUpperLineP1(p1, p2, 2);
        Point upperP2 = rotationCalculator_->calcUpperLineP2(p1, p2, 2);
        Point lowerP1 = rotationCalculator_->calcLowerLineP1(p1, p2, 2);
        Point lowerP2 = rotationCalculator_->calcLowerLineP2(p1, p2, 2);

        sf::Vertex line[] =
                {
                        sf::Vertex(sf::Vector2f(upperP1.x, upperP1.y), sf::Color::Red),
                        sf::Vertex(sf::Vector2f(upperP2.x, upperP2.y), sf::Color::Red),
                        sf::Vertex(sf::Vector2f(lowerP1.x, lowerP1.y), sf::Color::Red),
                        sf::Vertex(sf::Vector2f(lowerP2.x, lowerP2.y), sf::Color::Red)
                };

        window_->draw(line, 4, sf::Lines);
        //window_->drawDottedLine(p1.x, p1.y, p2.x, p2.y);
    }
    for (auto const& node : g->nodes) {
        sf::CircleShape c(10);
        c.setPosition(node.second->getPosition().x-10, node.second->getPosition().y-10);
        c.setFillColor(sf::Color(200, 200, 150));
        window_->draw(c);
    }
}