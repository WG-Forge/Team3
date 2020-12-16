#include <graph-components/Town.h>
#include <graph-components/Market.h>
#include <graph-components/Storage.h>
#include "MoveAgent.h"

Node* MoveAgent::move(const std::vector<Node *> &g, Train* train) {
    int newNode;
    if (train->getGoodsType() == Train::NOTHING) {
        newNode = moveTo(g, train, 2); // move to market
    } else {
        newNode = moveTo(g, train, 1); // move to home
    }
    return g[newNode];
}

int MoveAgent::moveTo(const std::vector<Node *> &g, Train* train, uint32_t buildingType) {
    const Edge* trainEdge = train->getEdge();
    int s1 = trainEdge->getFirstNode()->getPointIdx();
    int s2 = trainEdge->getSecondNode()->getPointIdx();

    std::vector<int> dist(g.size(), INF);
    std::vector<int> p(g.size());
    std::set < std::pair<int,int> > q;

    dist[s1] = train->getPosition();
    q.insert (std::make_pair (dist[s1], s1));
    dist[s2] = trainEdge->getLength() - train->getPosition();
    q.insert (std::make_pair (dist[s2], s2));
    int end_v;

    // dijkstra
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase (q.begin());

        if (g[v]->getType() == buildingType) {
            if ((buildingType == 1 && ((Town*) g[v])->isMine())
                || (buildingType == 2 && ((Market*) g[v])->getProduct() > 0)
                   || (buildingType == 3 && ((Storage*) g[v])->getArmor() > 0)) {
                end_v = v;
                break;
            }
        }

        for (auto edge : g[v]->getNeighbors()) {
            int to = edge->getFirstNode()->getPointIdx()
                     ? edge->getFirstNode()->getPointIdx() != v
                     : edge->getSecondNode()->getPointIdx();
            int len = edge->getLength();
            if (dist[v] + len < dist[to]) {
                q.erase (std::make_pair (dist[to], to));
                dist[to] = dist[v] + len;
                p[to] = v;
                q.insert (std::make_pair (dist[to], to));
            }
        }
    }

    // path recovery
    int prev;
    int v = end_v;
    while (v != s1 && v != s2) {
        prev = v;
        v=p[v];
    }
    if (dist[v] == 0) {
        return prev;
    } else {
        return v;
    }
}
