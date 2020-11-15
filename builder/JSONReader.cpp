
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
    std::map<int, std::shared_ptr<Node>> nodes;
    std::unique_ptr<Graph> graph(new Graph(root["idx"].asInt(), root["name"].asString()));
//            Graph graph(root["idx"].asInt(), root["name"].asString());
    for (auto point : root["points"]){
        int idx = point["idx"].asInt(), post_idx = point["post_idx"].asInt();
        nodes[idx] = std::make_shared<Node>(idx, post_idx);
        graph->addNode(nodes[idx]);
    }
//    for (const auto& noda : nodes){
//        std::cout << "\n\n noda idx - " << noda.first;
//        std::cout << "\n noda post_idx - " << *(noda.second);
//    }
//    std::cout << "after nodes\n";
    for(auto line : root["lines"]){
        graph->addEdge(std::make_unique<Edge>(line["idx"].asInt(),
                                             line["length"].asInt(),
                                             std::move(nodes[line["points"][0].asInt()]),
                                             std::move(nodes[line["points"][1].asInt()])));
    }

//    std::cout << "after edges\n" << graph->nodes[7]->idx_;
//    return std::move(std::make_unique<Graph>(graph));
    return std::move(graph);
}
