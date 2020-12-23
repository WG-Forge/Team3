#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <Point.h>

class Edge;

class Node {
public:
    constexpr static uint32_t TYPE = 0;

private:
    const uint32_t type_;

protected:
    const int32_t pointIdx_; //same as idx for layer 0, layer 10 and point_idx for layer 1
    const int32_t postIdx_; //same as post_idx for layer 0 and idx for layer 1, omitted for layer10

    Point coordinates_;

    std::vector<Edge*> neighbors_;

public:
    Node() = delete;
    Node(int32_t pointIdx, int32_t postIdx, uint32_t type = 0);

    uint32_t getType() const;
    int32_t getPointIdx() const;
    int32_t getPostIdx() const;
    Point getCoordinates() const;
    std::vector<Edge*>& getNeighbors();

    void setCoordinates(uint32_t x, uint32_t y);

    void addNeighbor(Edge* incidentEdge);
};
