#include <JSONParser.h>

//TODO Handle exceptions, possibly thrown by JSONParser::parse(const std::string& rawJson) (if its needed (?))
std::pair<Json::ValueConstIterator, Json::ValueConstIterator> JSONParser::parse(const std::string &rawJson) {
    root_.clear();

    std::unique_ptr<Json::CharReader> reader(readerBuilder_.newCharReader());
    std::string errors;

    if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.size(), &root_, &errors)) {
        throw std::runtime_error(errors);
    }

    return std::make_pair(root_.begin(), root_.end());
}
