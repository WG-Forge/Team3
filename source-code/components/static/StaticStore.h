#ifndef TEAM3_STATICSTORE_H
#define TEAM3_STATICSTORE_H

#include <iostream>
#include <unordered_map>
#include <components/map-objects/Train.h>
#include <components/map-objects/Post.h>

class StaticStore {
public:
    static std::unordered_map<int, Node*> nodes;
    static std::unordered_map<int, Edge*> edges;
    static std::unordered_map<int, Post*> posts;
    static std::unordered_map<int, Train*> trains;
};

#endif //TEAM3_STATICSTORE_H
