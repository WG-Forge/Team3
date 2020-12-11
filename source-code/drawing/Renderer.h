#ifndef TEAM3_RENDERER_H
#define TEAM3_RENDERER_H

#include <memory>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <components/graph/Graph.h>
#include <utils/RotationCalculator.h>
#include "AssetManager.h"

class Renderer {
private:
    sf::RenderWindow* window_;
    RotationCalculator rotationCalculator_;
    AssetManager assetManager_;
    const int NODE_SIZE_ = 10;
    const int TRAIN_SIZE_ = 8;
    const int RAIL_DIST = 1;
    void renderEdges(Graph* g);
    void renderNodes(Graph* g);
    void renderTrains(Graph* g);
public:
    Renderer(sf::RenderWindow* window);
    void render(Graph* g);
};


#endif //TEAM3_RENDERER_H
