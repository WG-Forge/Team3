#pragma once

#include <vector>
#include <memory>
#include <limits>
#include <utility>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include <graph/Graph.h>

#include <boost/graph/topology.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/random_layout.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/gursoy_atun_layout.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/kamada_kawai_spring_layout.hpp>

namespace layout {
    constexpr uint32_t stepCount = 2500;

    typedef boost::square_topology<>::point_type BoostPoint;

    struct EdgeProperty {
        explicit EdgeProperty(const double length) : length(length) {
        }

        double length;
    };

    struct VertexProperty {
        BoostPoint point;
    };

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty> BoostGraph;
    typedef boost::property_map<BoostGraph, BoostPoint VertexProperty::*>::type PositionMap;

    void graphLayout(Graph &graph, uint32_t leftX, uint32_t topY, uint32_t rightX, uint32_t bottomY);
}
