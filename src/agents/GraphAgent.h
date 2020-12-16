#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <Node.h>
#include <Town.h>
#include <Market.h>
#include <Storage.h>
#include <Hometown.h>
#include <EdgeCreationHelper.h>

//TODO Move working with graph creation to GraphAgent if possible

class Observer;

class GraphAgent {
private:
    //If you are not trying to modify parsing for layers just skip this section
    std::vector<EdgeCreationHelper> edgeCreationHelpers_;

    friend class Observer;

private:
    std::map<int32_t, uint32_t> pointIdxCompression_;
    std::unordered_map<int32_t, Edge*> lineIdxToEdge_;
    std::vector<Node*> graph_;

public:
    GraphAgent();

    std::vector<Node*>& getGraph();
    Edge* findEdge(uint32_t lineIdx);
    uint32_t compressPointIdx(uint32_t idx);

    void mapEdge(Edge* edge);
};
