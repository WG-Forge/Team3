#pragma once

#include <memory>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Node.h>
#include <Edge.h>
#include <Town.h>
#include <Market.h>
#include <Storage.h>
#include <RotationCalculator.h>
#include <ResourceManager.h>
#include <defines.h>
#include <game-components/Train.h>

class Renderer {
private:
    sf::RenderWindow* window_;
    RotationCalculator rotationCalculator_;
    ResourceManager resourceManager;
    const int32_t NODE_SIZE_ = 10;
    const int32_t TRAIN_SIZE_ = 4;
    const int32_t RAIL_DIST = 1;
public:
    explicit Renderer(sf::RenderWindow* window);
    void renderEdges(const std::vector<Node*>& g);
    void renderNodes(const std::vector<Node*>& g);
    void renderTrains(const std::vector<Train*>& trains);
    void renderTownsInfo(const std::vector<Node*>& g);
    void render(const std::vector<Node*>& g, const std::vector<Train*>& trains);
    void renderDebugInfo(const std::vector<Node*>& g);
};
