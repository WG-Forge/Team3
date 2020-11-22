#include "JSONReader.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <iostream>
#include <graph/Market.h>
#include <graph/City.h>
#include <graph/Storage.h>

//JSONReader::JSONReader(std::string fileName): fileName_(std::move(fileName)){}
//
//void JSONReader::setFileName(std::string fileName) {
//    fileName_ = std::move(fileName);
//}
enum TYPES {CITY = 1, MARKET, STORAGE};

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

    std::map<int, Node*> nodes;
    std::unique_ptr<Graph> graph(new Graph(root["idx"].asInt(), root["name"].asString()));

    for (auto point : root["points"]) {
        int idx = point["idx"].asInt(), post_idx = point["post_idx"].asInt();
        std::unique_ptr<Node> temp = std::make_unique<Node>(idx, post_idx);
        nodes[idx] = temp.get();
        graph->addNode(std::move(temp));
    }

//    std::cout << "after nodes\n";
    for(auto line : root["lines"]){
        graph->addEdge(std::make_unique<Edge>(line["idx"].asInt(),
                                             line["length"].asInt(),
                                             nodes[line["points"][0].asInt()],
                                             nodes[line["points"][1].asInt()]));
    }

//    std::cout << "after edges\n" << graph->nodes[1]->idx_;
    return std::move(graph);
}

std::unique_ptr<Graph> JSONReader::readLayer1(const std::string &fileName) {

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

    std::map<int, Node*> nodes;
    std::unique_ptr<Graph> graph(new Graph(root["idx"].asInt(), root["name"].asString()));

    for (auto post : root["posts"]){
        std::unique_ptr<Node> temp;
        int type = post["type"].isInt();
        switch (type) {
            case CITY:
                temp = std::make_unique<City>( post["idx"].asInt(),
                                             post["point_idx"].asInt(),
                                             post["armor"].asInt(),
                                             post["armor_capacity"].asInt(),
                                             post["level"].asInt(),
                                             post["name"].asString(),
                                             post["next_level_price"].asInt(),
                                             post["player_idx"].asString(),
                                             post["population"].asInt(),
                                             post["population_capacity"].asInt(),
                                             post["product"].asInt(),
                                             post["product_capacity"].asInt(),
                                             post["train_cooldown"].asInt());
                nodes[post["idx"].asInt()] = temp.get();
                break;
            case MARKET:
                temp = std::make_unique<Market>( post["idx"].asInt(),
                                               post["point_idx"].asInt(),
                                               post["name"].asString(),
                                               post["product"].asInt(),
                                               post["product_capacity"].asInt(),
                                               post["replenishment"].asInt());
                nodes[post["idx"].asInt()] = temp.get();
                break;
            case STORAGE:
                temp = std::make_unique<Storage>( post["idx"].asInt(),
                                               post["point_idx"].asInt(),
                                               post["armor"].asInt(),
                                               post["armor_capacity"].asInt(),
                                               post["name"].asString(),
                                               post["replenishment"].asInt());
                nodes[post["idx"].asInt()] = temp.get();

                break;
            default:
                throw std::invalid_argument("Unknown type");
                break;
        }
        graph->addNode(std::move(temp));
    }



    return std::move(graph);
}
