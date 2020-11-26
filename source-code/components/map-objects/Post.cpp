#include <components/graph/Graph.h>
#include "Post.h"

Post::Post(int idx): idx_(idx) {}

void Post::readLayer1(Json::Value root) {
    name_ = root["name"].asString();
}
