#ifndef TEAM3_JSONREADER_H
#define TEAM3_JSONREADER_H

#include <graph/Graph.h>
#include <json/json.h>


class JSONReader {
public:
    JSONReader() = default;
    static std::unique_ptr<Graph> readGraph(const std::string& fileName);
    static std::unique_ptr<Graph> readLayer1(const std::string& fileName);
    static std::unique_ptr<Graph> readLayer0(const std::string& fileName);

private:
    static std::unique_ptr<Graph> parseLayer0(Json::Value root);

};

#endif
