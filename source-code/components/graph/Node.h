#ifndef TEAM3_NODE_H
#define TEAM3_NODE_H
#pragma once
#include <memory>
#include <drawing/Point.h>
#include <json/json.h>

class Post;

class Node {
protected:
    int idx_;
    int post_idx_;
    Point position_;
public:
    Post* post = nullptr;
    Node(int idx, int post_idx);

    void setPosition(Point position);
    Point getPosition() const;
    int getId();

    void readLayer0(Json::Value root);
};


#endif //TEAM3_NODE_H
