#ifndef TEAM3_RENDERER_H
#define TEAM3_RENDERER_H

#include <memory>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "graph/Graph.h"
#include "utils/RotationCalculator.h"
#include "AssetManager.h"

class Renderer {
private:
    sf::RenderWindow* window_;
    RotationCalculator rotationCalculator_;
    AssetManager assetManager;
public:
    Renderer(sf::RenderWindow* window);
    void render(Graph* g);
};


#endif //TEAM3_RENDERER_H
