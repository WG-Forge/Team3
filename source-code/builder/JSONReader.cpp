#include "JSONReader.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <iostream>
#include <components/map-objects/Market.h>
#include <components/map-objects/City.h>
#include <components/map-objects/Storage.h>
#include <components/static/StaticStore.h>

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

    parseLayer0(root);
}

//std::unique_ptr<Graph> JSONReader::readLayer1(const std::string& rawJson) {
//
//    const auto rawJsonLength = static_cast<int>(rawJson.length());
//    JSONCPP_STRING err;
//    Json::Value root;
//
//    Json::CharReaderBuilder builder;
//    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
//    if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err)) {
//        throw std::invalid_argument("Error");
//    }
//
//    std::map<int, Node*> nodes;
//    std::unique_ptr<Graph> graph(new Graph(root["idx"].asInt(), root["name"].asString()));
//
//    for (auto post : root["posts"]){
//        std::unique_ptr<Node> temp;
//        int type = post["type"].isInt();
//        switch (type) {
//            case CITY:
//                temp = std::make_unique<City>( post["idx"].asInt(),
//                                             post["point_idx"].asInt(),
//                                             post["armor"].asInt(),
//                                             post["armor_capacity"].asInt(),
//                                             post["level"].asInt(),
//                                             post["name"].asString(),
//                                             post["next_level_price"].asInt(),
//                                             post["player_idx"].asString(),
//                                             post["population"].asInt(),
//                                             post["population_capacity"].asInt(),
//                                             post["product"].asInt(),
//                                             post["product_capacity"].asInt(),
//                                             post["train_cooldown"].asInt());
//                nodes[post["idx"].asInt()] = temp.get();
//                break;
//            case MARKET:
//                temp = std::make_unique<Market>( post["idx"].asInt(),
//                                               post["point_idx"].asInt(),
//                                               post["name"].asString(),
//                                               post["product"].asInt(),
//                                               post["product_capacity"].asInt(),
//                                               post["replenishment"].asInt());
//                nodes[post["idx"].asInt()] = temp.get();
//                break;
//            case STORAGE:
//                temp = std::make_unique<Storage>( post["idx"].asInt(),
//                                               post["point_idx"].asInt(),
//                                               post["armor"].asInt(),
//                                               post["armor_capacity"].asInt(),
//                                               post["name"].asString(),
//                                               post["replenishment"].asInt());
//                nodes[post["idx"].asInt()] = temp.get();
//
//                break;
//            default:
//                throw std::invalid_argument("Unknown type");
//                break;
//        }
//        graph->addNode(std::move(temp));
//    }
//
//    return std::move(graph);
//}


std::unique_ptr<Graph> JSONReader::parseLayer0(Json::Value root){
    std::map<int, Node*> nodes;
    std::unique_ptr<Graph> graph(new Graph(root["idx"].asInt(), root["name"].asString()));

    for (auto point : root["points"]) {
        int idx = point["idx"].asInt(), post_idx = point["post_idx"].asInt();
        std::unique_ptr<Node> temp = std::make_unique<Node>(idx, post_idx);
        nodes[idx] = temp.get();
        graph->addNode(std::move(temp));
        StaticStore::nodes[post_idx] = temp.get();
    }

//    std::cout << "after nodes\n";
    for(auto line : root["lines"]){
        graph->addEdge(std::make_unique<Edge>(line["idx"].asInt(),
                                              line["length"].asDouble(),
                                              nodes[line["points"][0].asInt()],
                                              nodes[line["points"][1].asInt()]));
    }

//    std::cout << "after edges\n" << components->nodes[1]->idx_;
    return std::move(graph);
}

void JSONReader::readLayer10(const std::string &rawJson, std::unique_ptr<Graph> graph) {
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
}



