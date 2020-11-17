
#include "JSONReader.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <utility>

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

    std::map<int, std::unique_ptr<Node>> nodes;
    std::unique_ptr<Graph> graph(new Graph(root["idx"].asInt(), root["name"].asString()));

    for (auto point : root["points"]) {
        int idx = point["idx"].asInt(), post_idx = point["post_idx"].asInt();
        nodes[idx] = std::make_unique<Node>(idx, post_idx);
        graph->addNode(std::move(nodes[idx]));
    }

//    std::cout << "after nodes\n";
    for(auto line : root["lines"]){
        graph->addEdge(std::make_unique<Edge>(line["idx"].asInt(),
                                             line["length"].asInt(),
                                             nodes[line["points"][0].asInt()].get(),
                                             nodes[line["points"][1].asInt()].get()));
    }

//    std::cout << "after edges\n" << graph->nodes[1]->idx_;
    return std::move(graph);
}
