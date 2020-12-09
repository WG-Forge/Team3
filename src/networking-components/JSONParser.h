#pragma once

#include <memory>
#include <json/json.h>

class JSONParser {
private:
    Json::Value root_;
    Json::CharReaderBuilder readerBuilder_;

public:
    //TODO Add modifying stack size (if its needed (?))

    //Every next call invalidates all the previous iterators
    //Take care about data preserving
    std::pair<Json::ValueConstIterator, Json::ValueConstIterator> parse(const std::string& rawJson);
};
