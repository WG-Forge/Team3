#include <Renderer.h>

Renderer::Renderer(sf::RenderWindow *window)
        : window_(window) {}

void Renderer::render(const std::vector<Node*>& g) {

    for (const auto* node : g) {
        sf::Sprite s;
        sf::Texture* texture;

        switch (node->getType()) {
            case Node::TYPE :
                texture = assetManager_.getOrLoadAsset(std::string(defines::render_info::NODE_ASSET_PATH));
                break;

            case Town::TYPE :
                texture = assetManager_.getOrLoadAsset(std::string(defines::render_info::TOWN_ASSET_PATH));
                break;

            case Market::TYPE :
                texture = assetManager_.getOrLoadAsset(std::string(defines::render_info::MARKET_ASSET_PATH));
                break;

            case Storage::TYPE :
                texture = assetManager_.getOrLoadAsset(std::string(defines::render_info::STORAGE_ASSET_PATH));
                break;
        }

        s = sf::Sprite(*texture);
        s.scale((float) NODE_SIZE_ / texture->getSize().x,
                (float) NODE_SIZE_ / texture->getSize().y);
        s.setPosition(node->getCoordinates().x - NODE_SIZE_/2,
                      node->getCoordinates().y - NODE_SIZE_/2);
        window_->draw(s);
    }

    for (auto* node : g) {
        for (auto& edge : node->getNeighbors()) {
            Point p1 = Point(edge->getFirstNode()->getCoordinates());
            Point p2 = Point(edge->getSecondNode()->getCoordinates());
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
            //window_->drawDottedLine(p1.x, p1.y, p2.x, p2.y);
        }
    }
}
