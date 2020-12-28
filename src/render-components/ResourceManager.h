#pragma once

#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

class ResourceManager {
private:
    std::map<std::string, std::unique_ptr<sf::Texture>> assets_;
    std::map<std::string, std::unique_ptr<sf::Font>> fonts_;
    const std::string PREFIX = "../";
    //const std::string PREFIX = "../../";
public:
    sf::Texture* getOrLoadAsset(const std::string& path);
    sf::Font* getOrLoadFont(const std::string& path);
};
