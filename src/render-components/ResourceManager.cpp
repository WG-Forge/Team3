#include <ResourceManager.h>

sf::Texture *ResourceManager::getOrLoadAsset(const std::string& path) {
    std::string full_path = PREFIX + path;
    auto &asset = assets_[path];
    if (!asset) {
        asset = std::make_unique<sf::Texture>();
        asset->loadFromFile(full_path);
    }
    return asset.get();
}

sf::Font *ResourceManager::getOrLoadFont(const std::string &path) {
    std::string full_path = PREFIX + path;
    auto &font = fonts_[path];
    if (!font) {
        font = std::make_unique<sf::Font>();
        font->loadFromFile(full_path);
    }
    return font.get();
}
