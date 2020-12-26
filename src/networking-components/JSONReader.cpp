#include <JSONReader.h>

//TODO NEWEST: Throw error codes, not exceptions, if possible (requires reading documentation for jsoncpp)
//TODO Handle exceptions, possibly thrown by JSONReader::read(const std::string& rawJson) (if its needed (?))

JSON_OBJECT_AS_MAP JSONReader::read(const std::string &rawJson) {
    root_.clear();

    std::unique_ptr<Json::CharReader> reader(readerBuilder_.newCharReader());
    std::string errors;

    if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.size(), &root_, &errors)) {
        throw std::runtime_error(errors);
    }

    return root_;
}
