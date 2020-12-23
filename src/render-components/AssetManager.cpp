#include <AssetManager.h>

sf::Texture *AssetManager::getOrLoadAsset(const std::string& path) {
    std::string full_path = "../" + path;
    auto &asset = assets_[path];
    if (!asset) {
        asset = std::make_unique<sf::Texture>();
        asset->loadFromFile(full_path);
        //asset->loadFromFile(path);
    }
    return asset.get();
}
