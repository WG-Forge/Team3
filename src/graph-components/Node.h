#pragma once

#include <cstdint>
#include <vector>
#include <Point.h>

class Edge;

class Node {
public:
    constexpr static uint32_t TYPE = 0;

protected:
    const int32_t pointIdx_; //same as idx for layer 0 and layer 10
    const int32_t postIdx_; //same as post_idx for layer 0 and idx for layer 1

    const Point coordinates_;

    std::vector<Edge*> neighbors_;

public:
    Node() = delete;
    Node(int32_t pointIdx, int32_t postIdx, Point coordinates);

    int32_t getPointIdx() const;
    int32_t getPostIdx() const;
    Point getCoordinates() const;

    void addNeighbor(Edge* incidentEdge);
};
