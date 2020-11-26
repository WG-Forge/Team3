#include "StaticStore.h"

std::unordered_map<int, Node*> StaticStore::nodes;
std::unordered_map<int, Edge*> StaticStore::edges;
std::unordered_map<int, Post*> StaticStore::posts;
std::unordered_map<int, Train*> StaticStore::trains;

