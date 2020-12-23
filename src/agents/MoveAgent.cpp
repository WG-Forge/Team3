#include <Town.h>
#include <Market.h>
#include <Storage.h>
#include <MoveAgent.h>

TrainMovement MoveAgent::move(std::vector<Node*>& graph, const std::map<int32_t, uint32_t>& pointIdxCompression, Train* train) {
    Node* newNode;
    if (train->getGoods() == 0) {
        newNode = moveTo(graph, pointIdxCompression, train, 2); // move to market
    } else {
        newNode = moveTo(graph, pointIdxCompression, train, 1); // move to home
    }
    return calcMovement(train, newNode);
}

Node* MoveAgent::moveTo(std::vector<Node*>& graph, const std::map<int32_t, uint32_t>& pointIdxCompression,
                        Train* train, uint32_t buildingType) {
    const Edge* trainEdge = train->getEdge();
    int32_t s1 = pointIdxCompression.at(trainEdge->getFirstNode()->getPointIdx());
    int32_t s2 = pointIdxCompression.at(trainEdge->getSecondNode()->getPointIdx());

    std::vector<int32_t> dist(graph.size(), INF);
    std::vector<int32_t> p(graph.size());
    std::set < std::pair<int32_t,int32_t> > q;

    dist[s1] = train->getPosition();
    q.insert (std::make_pair (dist[s1], s1));
    dist[s2] = trainEdge->getLength() - train->getPosition();
    q.insert (std::make_pair (dist[s2], s2));
    int32_t end_v = -1;

    // dijkstra
    while (!q.empty()) {
        int32_t v = q.begin()->second;
        q.erase (q.begin());

        if (graph[v]->getType() == buildingType) {
            if ((buildingType == 1 && ((Town*) graph[v])->isMine())
                || (buildingType == 2 && ((Market*) graph[v])->getProduct() > 0)
                   || (buildingType == 3 && ((Storage*) graph[v])->getArmor() > 0)) {
                end_v = v;
                break;
            }
        }

        for (auto edge : graph[v]->getNeighbors()) {
            int32_t toOrigIdx = pointIdxCompression.at(edge->getFirstNode()->getPointIdx()) != v
                     ? edge->getFirstNode()->getPointIdx()
                     : edge->getSecondNode()->getPointIdx();
            int32_t to = pointIdxCompression.at(toOrigIdx);
            int32_t len = edge->getLength();
            if (dist[v] + len < dist[to]) {
                q.erase (std::make_pair (dist[to], to));
                dist[to] = dist[v] + len;
                p[to] = v;
                q.insert (std::make_pair (dist[to], to));
            }
        }
    }

    // path recovery
    if (end_v == -1) {
        return nullptr;
    }
    int32_t prev = -1;
    int32_t v = end_v;
    while (v != s1 && v != s2) {
        prev = v;
        v=p[v];
    }
    if (dist[v] == 0) {
        if (prev != -1) {
            return graph[prev];
        } else {
            return nullptr;
        }
    } else {
        return graph[v];
    }
}

TrainMovement MoveAgent::calcMovement(Train *train, Node* nextNode) {
    if (nextNode == nullptr) {
        return TrainMovement(train->getEdge()->getLineIdx(), 0, train->getIdx());
    }
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
    int32_t speed;
    if (nextNode->getPointIdx() == movementEdge->getFirstNode()->getPointIdx()) {
        speed = -1;
    } else {
        speed = 1;
    }
    return TrainMovement(movementEdge->getLineIdx(), speed, train->getIdx());
}


TrainMovement::TrainMovement(int32_t lineIdx, int32_t speed, int32_t trainIdx) : lineIdx(lineIdx), speed(speed),
                                                                                 trainIdx(trainIdx) {}
