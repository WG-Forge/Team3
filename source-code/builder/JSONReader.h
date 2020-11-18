#ifndef TEAM3_JSONREADER_H
#define TEAM3_JSONREADER_H

//#include <jsoncpp/json/json.h>
#include <graph/Graph.h>
#include <dist/json/json.h>


class JSONReader {
public:
//    explicit JSONReader(std::string fileName);
    JSONReader() = default;
    static std::unique_ptr<Graph> readGraph(const std::string& fileName);

//private:
//    std::string fileName_;
};

#endif
