#include "AssetManager.h"

sf::Texture *AssetManager::getOrLoadAsset(std::string path) {
    auto &asset = assets_[path];
    if (!asset) {
        asset = std::make_unique<sf::Texture>();
        asset->loadFromFile(path);
    }
    return asset.get();
}
