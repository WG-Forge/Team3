#ifndef TEAM3_NODE_H
#define TEAM3_NODE_H

#include <memory>
#include <drawing/Point.h>

class Node {
private:
    int post_idx_;
    Point position_;
public:
    int idx_;
    Node(int idx, int post_idx);
    void setPosition(Point position);
    Point getPosition() const;
};


#endif //TEAM3_NODE_H
