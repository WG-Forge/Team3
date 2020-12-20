#pragma once

#include <memory>
#include <json/json.h>

//TODO Add modifying stack size (if its needed (?))

typedef Json::Value JSON_OBJECT_AS_MAP;
typedef Json::ValueType JSON_VALUE_TYPE;

class JSONReader {
private:
    Json::Value root_;
    Json::CharReaderBuilder readerBuilder_;

public:
    //Every next call invalidates all the previous iterators
    //Take care about data preserving
    JSON_OBJECT_AS_MAP read(const std::string& rawJson);
};
