#ifndef TEAM3_POST_H
#define TEAM3_POST_H
#include <json/json.h>

enum Type { DEFAULT = 0, CITY = 1, MARKET = 2, STORAGE = 3};

class Post {
protected:
    std::string name_;
    int idx_;
    std::string asset_;
public:
    explicit Post(int idx);
    explicit Post(int idx, std::string asset);
    virtual void readLayer1(Json::Value root);
    const std::string &getAsset() const;
};


#endif //TEAM3_POST_H
