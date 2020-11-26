#ifndef TEAM3_NODE_H
#define TEAM3_NODE_H

#include <memory>
#include <drawing/Point.h>
#include <json/json.h>
#include <components/map-objects/Post.h>

class Node {
protected:
    int idx_;
    int post_idx_;
    Point position_;
    std::unique_ptr<Post> post_;
public:
    Node(int idx, int post_idx);

    void setPosition(Point position);
    Point getPosition() const;
    int getId();
    void setPost(std::unique_ptr<Post> post);
};


#endif //TEAM3_NODE_H
