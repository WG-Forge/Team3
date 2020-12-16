#include <graph-components/Town.h>
#include <graph-components/Market.h>
#include <graph-components/Storage.h>
#include "MoveAgent.h"

TrainMovement MoveAgent::move(GraphAgent* graphAgent, Train* train) {
    Node* newNode;
    if (train->getGoodsType() == Train::NOTHING) {
        newNode = moveTo(graphAgent, train, 2); // move to market
    } else {
        newNode = moveTo(graphAgent, train, 1); // move to home
    }
    return calcMovement(graphAgent, train, newNode);
}

Node* MoveAgent::moveTo(GraphAgent* graphAgent, Train* train, uint32_t buildingType) {
    auto g = graphAgent->getGraph();
    const Edge* trainEdge = train->getEdge();
    int s1 = graphAgent->compressPointIdx(trainEdge->getFirstNode()->getPointIdx());
    int s2 = graphAgent->compressPointIdx(trainEdge->getSecondNode()->getPointIdx());

    std::vector<int> dist(g.size(), INF);
    std::vector<int> p(g.size());
    std::set < std::pair<int,int> > q;

    dist[s1] = train->getPosition();
    q.insert (std::make_pair (dist[s1], s1));
    dist[s2] = trainEdge->getLength() - train->getPosition();
    q.insert (std::make_pair (dist[s2], s2));
    int end_v = s1;

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
            int toOrigIdx = edge->getFirstNode()->getPointIdx() != v
                     ? edge->getFirstNode()->getPointIdx()
                     : edge->getSecondNode()->getPointIdx();
            int to = graphAgent->compressPointIdx(toOrigIdx);
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
        return g[prev];
    } else {
        return g[v];
    }
}

TrainMovement MoveAgent::calcMovement(GraphAgent *graphAgent, Train *train, Node* nextNode) {
    const Edge* movementEdge;
    uint32_t currentNode;

    if (train->getPosition() == 0) {
        currentNode = train->getEdge()->getFirstNode()->getPointIdx();
    } else if (train->getPosition() == train->getEdge()->getLength()) {
        currentNode = train->getEdge()->getSecondNode()->getPointIdx();
    }

    if (train->getPosition() == 0 || train->getPosition() == train->getEdge()->getLength()) {
        for (auto edge : nextNode->getNeighbors()) {
            if (currentNode == edge->getFirstNode()->getPointIdx()
                || currentNode == edge->getSecondNode()->getPointIdx()) {
                movementEdge = edge;
                break;
            }
        }
    } else {
        movementEdge = train->getEdge();
    }
    int speed;
    if (nextNode->getPointIdx() == movementEdge->getFirstNode()->getPointIdx()) {
        speed = -1;
    } else {
        speed = 1;
    }
    return TrainMovement(movementEdge->getLineIdx(), speed, train->getIdx());
}


TrainMovement::TrainMovement(int32_t lineIdx, int32_t speed, int32_t trainIdx) : lineIdx(lineIdx), speed(speed),
                                                                                 trainIdx(trainIdx) {}
