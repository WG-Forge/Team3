#pragma once

#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

class AssetManager {
private:
    std::map<std::string, std::unique_ptr<sf::Texture>> assets_;
public:
    sf::Texture* getOrLoadAsset(std::string path);
};
