#include <components/graph/Graph.h>
#include <components/static/StaticStore.h>
#include "Post.h"

Post::Post(int idx) : idx_(idx){}

void Post::readLayer1(Json::Value root) {
    name_ = root["name"].asString();
    const auto & point_idx = root["point_idx"];
    if (point_idx != nullptr) {
        node = StaticStore::nodes[point_idx.asInt()];
        if (node) {
            Post::node->post = this;
        }
    } else {
        std::invalid_argument("point_idx can't be nullptr");
    }

}
