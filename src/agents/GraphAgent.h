#pragma once

#include <vector>
#include <map>
#include <Node.h>
#include <Town.h>
#include <Market.h>
#include <Storage.h>
#include <EdgeCreationHelper.h>

class Observer;

class GraphAgent {
private:
    //If you are not trying to modify parsing for layers just skip this section
    std::vector<EdgeCreationHelper> edgeCreationHelpers_;

    friend class Observer;

private:
    std::map<int32_t, uint32_t> pointIdxCompression_;
    std::vector<Node*> graph_;

public:
    GraphAgent();

    std::vector<Node*>& getGraph();
};
