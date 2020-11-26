#ifndef TEAM3_POST_H
#define TEAM3_POST_H
#include <json/json.h>

enum Type { DEFAULT = 0, CITY = 1, MARKET = 2, STORAGE = 3};

class Post {
protected:
    std::string name_;
    int idx_;

public:
    explicit Post(int idx);
    virtual void readLayer1(Json::Value root);
};


#endif //TEAM3_POST_H
