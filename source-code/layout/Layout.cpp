#include "Layout.h"

namespace layout {
    void graphLayout(Graph &graph, uint32_t leftX, uint32_t topY, uint32_t rightX, uint32_t bottomY) {
        boost::rectangle_topology<> space(leftX, topY, rightX, bottomY);

        BoostGraph bGraph(graph.nodes.size());

        std::unordered_map<size_t, size_t> indexToRange;
        std::unordered_map<size_t, Node *> rangeToNode;

        size_t rangeIndex = 0;
        for (auto &vertex : graph.nodes) {
            indexToRange[vertex.second->getId()] = rangeIndex;
            rangeToNode[rangeIndex++] = vertex.second.get();
        }

        for (auto &edge : graph.edges) {
            boost::add_edge(boost::vertex(indexToRange[edge.second->getFirstNode()->getId()], bGraph),
                            boost::vertex(indexToRange[edge.second->getSecondNode()->getId()], bGraph),
                            EdgeProperty(edge.second->getLength()),
                            bGraph);
        }

        PositionMap positionMap = boost::get(&VertexProperty::point, bGraph);

        boost::random_graph_layout(bGraph, positionMap, space);
        boost::gursoy_atun_layout(bGraph, space, positionMap, stepCount);

        boost::graph_traits<BoostGraph>::vertex_iterator vI, vEnd;
        for (boost::tie(vI, vEnd) = boost::vertices(bGraph); *vI != graph.nodes.size(); ++vI) {
            rangeToNode[*vI]->setPosition(Point(positionMap[*vI][0], positionMap[*vI][1]));
        }
    }
}