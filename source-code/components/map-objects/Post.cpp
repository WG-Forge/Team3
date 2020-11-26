#include <components/graph/Graph.h>
#include "Post.h"

Post::Post(int idx)
            : idx_(idx)
            , asset_("resources/images/unknown.png") {}

void Post::readLayer1(Json::Value root) {
    name_ = root["name"].asString();
}

Post::Post(int idx, std::string asset)
                            : idx_(idx)
                            , asset_(asset) {}

const std::string &Post::getAsset() const {
    return asset_;
}
