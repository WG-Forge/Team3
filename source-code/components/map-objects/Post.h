#ifndef TEAM3_POST_H
#define TEAM3_POST_H
#include <json/json.h>
#include <components/graph/Node.h>

enum class Type { DEFAULT = 0, CITY, MARKET, STORAGE};

class Post {
protected:
    Node* node = nullptr;
    Type type = Type::DEFAULT;
    std::string name_;
    int idx_;

public:
    explicit Post(int idx);
    virtual void readLayer1(Json::Value root);
};


#endif //TEAM3_POST_H
