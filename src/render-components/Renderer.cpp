#include <Renderer.h>

Renderer::Renderer(sf::RenderWindow *window)
        : window_(window) {}

void Renderer::render(const std::vector<Node*>& g) {
    renderEdges(g);
    renderNodes(g);
}

void Renderer::renderEdges(const std::vector<Node*>& g) {
    for (auto* node : g) {
        for (auto& edge : node->getNeighbors()) {
            auto p1 = Point(edge->getFirstNode()->getCoordinates());
            auto p2 = Point(edge->getSecondNode()->getCoordinates());
            Point upperP1 = rotationCalculator_.calcUpperLineP1(p1, p2, RAIL_DIST);
            Point upperP2 = rotationCalculator_.calcUpperLineP2(p1, p2, RAIL_DIST);
            Point lowerP1 = rotationCalculator_.calcLowerLineP1(p1, p2, RAIL_DIST);
            Point lowerP2 = rotationCalculator_.calcLowerLineP2(p1, p2, RAIL_DIST);

            sf::Vertex line[] =
                    {
                            sf::Vertex(sf::Vector2f(upperP1.x, upperP1.y), sf::Color::Red),
                            sf::Vertex(sf::Vector2f(upperP2.x, upperP2.y), sf::Color::Red),
                            sf::Vertex(sf::Vector2f(lowerP1.x, lowerP1.y), sf::Color::Red),
                            sf::Vertex(sf::Vector2f(lowerP2.x, lowerP2.y), sf::Color::Red)
                    };

            window_->draw(line, 4, sf::Lines);
        }
    }
}

void Renderer::renderNodes(const std::vector<Node*>& g) {
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

            default :
                texture = assetManager_.getOrLoadAsset(std::string(defines::render_info::NODE_ASSET_PATH));
                break;
        }

        s = sf::Sprite(*texture);
        s.scale((float) NODE_SIZE_ / texture->getSize().x,
                (float) NODE_SIZE_ / texture->getSize().y);
        s.setOrigin((float) texture->getSize().x/2, (float) texture->getSize().y/2);
        s.setPosition(node->getCoordinates().x,
                      node->getCoordinates().y);
        window_->draw(s);
    }
}

/*void Renderer::renderTrains(const std::vector<Node*>& g) {
    for (auto const& edge : g->edges) {
        Train* train = edge.second->train;
        if (train != nullptr
            && train->getPosition() > 0
            && train->getPosition() < edge.second->getLength()) {
            Point p1 = Point(edge.second->getFirstNode()->getPosition());
            Point p2 = Point(edge.second->getSecondNode()->getPosition());
            Point train2DPosition = rotationCalculator_.calcPointOnLine(p1, p2, train->getPosition()/edge.second->getLength());
            sf::Sprite s;
            sf::Texture* texture;
            texture = assetManager_.getOrLoadAsset("resources/images/train.png");
            s = sf::Sprite(*texture);
            s.setOrigin(texture->getSize().x/2, texture->getSize().y/2);
            s.scale((float) TRAIN_SIZE_ / texture->getSize().x,
                    (float) TRAIN_SIZE_ / texture->getSize().y);
            s.setPosition(train2DPosition.x,
                          train2DPosition.y);
            s.rotate(rotationCalculator_.calcTrainRotation(p1, p2));
            window_->draw(s);
        }
    }
}*/