#ifndef TEAM3_JSONREADER_H
#define TEAM3_JSONREADER_H

#include <components/graph/Graph.h>
#include <json/json.h>


class JSONReader {
public:
    JSONReader() = default;
    static std::unique_ptr<Graph> readGraph(const std::string& fileName);
//    static std::unique_ptr<Graph> readLayer1(const std::string& rawJson);
    static std::unique_ptr<Graph> readLayer0(const std::string& rawJson);
    static void readLayer10(const std::string& rawJson, std::unique_ptr<Graph> graph);

private:
    static std::unique_ptr<Graph> parseLayer0(Json::Value root);

};

#endif
