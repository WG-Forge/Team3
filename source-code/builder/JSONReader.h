#ifndef TEAM3_JSONREADER_H
#define TEAM3_JSONREADER_H

#include <components/graph/Graph.h>
#include <json/json.h>
#include <game/GameMap.h>


class JSONReader {
public:
    JSONReader() = default;
    static std::unique_ptr<Graph> readGraph(const std::string& fileName);
    static void readLayer1(const std::string& rawJson, Graph* graph);
    static std::unique_ptr<Graph> readLayer0(const std::string& rawJson);
    static GameMap readLayer10(const std::string& rawJson, Graph* graph);

private:
    static std::unique_ptr<Graph> parseLayer0(Json::Value root);
};

#endif
