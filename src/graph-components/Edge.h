#pragma once

#include <cstdint>
#include <Node.h>

class Edge {
private:
    const int32_t lineIdx_;
    const uint32_t length_;

    Node* firstNode_;
    Node* secondNode_;

public:
    Edge() = delete;
    Edge(int32_t lineIdx, uint32_t length, Node* firstNode, Node* secondNode);

    int32_t getLineIdx() const;
    uint32_t getLength() const;

    Node* getFirstNode() const;
    Node* getSecondNode() const;
};
