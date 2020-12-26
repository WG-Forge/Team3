#pragma once

#include <Configuration.h>
#include <GraphAgent.h>
#include <Renderer.h>
#include <Camera.h>
#include <GameMapConfig.h>

class RenderAgent {
private:
    Configuration config_;
    std::shared_ptr<sf::RenderWindow> window_;
    Renderer renderer_;
    std::unique_ptr<Camera> camera_;
public:
    explicit RenderAgent(GameMapConfig map);
    explicit RenderAgent(Configuration config, GameMapConfig map);

    Renderer& getRenderer();
    std::unique_ptr<Camera>& getCamera();

    std::shared_ptr<sf::RenderWindow>& createWindow();
};
