#include "JSONReader.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <iostream>
#include <components/map-objects/Market.h>
#include <components/map-objects/City.h>
#include <components/map-objects/Storage.h>

//JSONReader::JSONReader(std::string fileName): fileName_(std::move(fileName)){}
//
//void JSONReader::setFileName(std::string fileName) {
//    fileName_ = std::move(fileName);
//}

std::unique_ptr<Graph> JSONReader::readGraph(const std::string& fileName) {
    Json::Value root;
    std::ifstream ifs;
    ifs.open(fileName);
    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;
    JSONCPP_STRING errs;

    if (!parseFromStream(builder, ifs, &root, &errs)) {
        std::cout << errs << std::endl;
        throw std::invalid_argument("error");
    }

    return parseLayer0(root);
}


std::unique_ptr<Graph> JSONReader::readLayer0(const std::string& rawJson) {
    const auto rawJsonLength = static_cast<int>(rawJson.length());
    JSONCPP_STRING err;
    Json::Value root;

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err)) {
        throw std::invalid_argument("Error");
    }

    return parseLayer0(root);
}

void JSONReader::readLayer1(const std::string& rawJson, Graph* graph) {

    const auto rawJsonLength = static_cast<int>(rawJson.length());
    JSONCPP_STRING err;
    Json::Value root;

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err)) {
        throw std::invalid_argument("Error");
    }

    for (const auto& post : root["posts"]) {
        int idx = post["idx"].asInt();
        std::string name = post["name"].asString();
        std::unique_ptr<Post> temp;

        switch (post["type"].asInt()) {
            case Type::CITY:
                temp = std::make_unique<City>(idx);
                break;
            case Type::MARKET:
                temp = std::make_unique<Market>(idx);
                break;
            case Type::STORAGE:
                temp = std::make_unique<Storage>(idx);
                break;
            default:
                temp = std::make_unique<Post>(idx);
                break;
        }
        temp->readLayer1(post);
        int point_idx = post["point_idx"].asInt();
        graph->nodes[point_idx]->setPost(std::move(temp));
    }
}


std::unique_ptr<Graph> JSONReader::parseLayer0(Json::Value root){
    std::map<int, Node*> nodes;
    std::unique_ptr<Graph> graph(new Graph(root["idx"].asInt(), root["name"].asString()));

    for (auto point : root["points"]) {
        int idx = point["idx"].asInt(), post_idx = point["post_idx"].asInt();
        std::unique_ptr<Node> temp = std::make_unique<Node>(idx, post_idx);
        nodes[idx] = temp.get();
        graph->addNode(std::move(temp));
    }

    for(auto line : root["lines"]){
        std::unique_ptr<Edge> temp = std::make_unique<Edge>(line["idx"].asInt(),
                                              line["length"].asDouble(),
                                              nodes[line["points"][0].asInt()],
                                              nodes[line["points"][1].asInt()]);
        graph->addEdge(std::move(temp));
    }

    return std::move(graph);
}

GameMap JSONReader::readLayer10(const std::string &rawJson, Graph* graph) {
    const auto rawJsonLength = static_cast<int>(rawJson.length());
    JSONCPP_STRING err;
    Json::Value root;

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err)) {
        throw std::invalid_argument("Error");
    }

    for (auto coordinate : root["coordinates"]){
        graph->nodes[coordinate["idx"].asInt()]->setPosition(Point(coordinate["x"].asInt(),
                                                             coordinate["y"].asInt()));
    }
    return {root["idx"].asInt(),
                   root["size"][0].asInt(),
                   root["size"][1].asInt()};
}



