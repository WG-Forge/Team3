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
#include <AssetManager.h>
#include <defines.h>

class Renderer {
private:
    sf::RenderWindow* window_;
    RotationCalculator rotationCalculator_;
    AssetManager assetManager_;
    const int32_t NODE_SIZE_ = 20;
public:
    Renderer(sf::RenderWindow* window);
    void render(const std::vector<Node*>& g);
};
