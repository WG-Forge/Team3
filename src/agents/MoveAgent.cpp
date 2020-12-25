#include <MoveAgent.h>

TrainMovement MoveAgent::move(std::vector<Node*>& graph,
                              const std::map<int32_t, uint32_t>& pointIdxCompression,
                              Train* train,
                              uint32_t building,
                              Hometown* home) {
    NextNode newNode;
    if (train->getGoods() != train->getGoodsCapacity()) {
        newNode = getNextNode(graph, pointIdxCompression, train,
                         PathSearchPreferences(0, building, nullptr));
    } else {
        newNode = getNextNode(graph, pointIdxCompression, train,
                         PathSearchPreferences(0, 1, nullptr));
    }
    TrainMovement movement = calcMovement(train, newNode.node);
    if (checkForSelfTrainsCollision(movement, home, train)) {
        return movement;
    } else {
        return TrainMovement(train->getEdge(), 0, train->getPosition(), train->getIdx());
    }
}

NextNode MoveAgent::getNextNode(std::vector<Node*>& graph,
                        const std::map<int32_t, uint32_t>& pointIdxCompression,
                        Train* train,
                        PathSearchPreferences prefs) {
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

        if (checkForDestination(graph[v], prefs)) {
            end_v = v;
            break;
        }

        for (auto edge : graph[v]->getNeighbors()) {
            int32_t toOrigIdx = pointIdxCompression.at(edge->getFirstNode()->getPointIdx()) != v
                     ? edge->getFirstNode()->getPointIdx()
                     : edge->getSecondNode()->getPointIdx();
            int32_t to = pointIdxCompression.at(toOrigIdx);
            if (checkForTransit(graph[to], prefs)) {
                int32_t len = edge->getLength();
                if (dist[v] + len < dist[to]) {
                    q.erase(std::make_pair(dist[to], to));
                    dist[to] = dist[v] + len;
                    p[to] = v;
                    q.insert(std::make_pair(dist[to], to));
                }
            }
        }
    }

    // path recovery
    if (end_v == -1) {
        return NextNode(nullptr, 0);
    }
    int32_t totalLength = dist[end_v];
    int32_t prev = -1;
    int32_t v = end_v;
    while (v != s1 && v != s2) {
        prev = v;
        v=p[v];
    }
    if (dist[v] == 0) {
        if (prev != -1) {
            return NextNode(graph[prev], totalLength);
        } else {
            return NextNode(nullptr, 0);;
        }
    } else {
        return NextNode(graph[v], totalLength);
    }
}

TrainMovement MoveAgent::calcMovement(Train *train, Node* nextNode) {
    if (nextNode == nullptr) {
        return TrainMovement(train->getEdge(),
                             0, train->getPosition(), train->getIdx());
    }
    const Edge* movementEdge;
    int32_t currentNode = -1;
    uint32_t newPosition;

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

    if (currentNode == movementEdge->getFirstNode()->getPointIdx()) {
        newPosition = 0;
    } else if (currentNode == movementEdge->getSecondNode()->getPointIdx()) {
        newPosition = movementEdge->getLength();
    } else {
        newPosition = train->getPosition();
    }
    newPosition += speed;

    return TrainMovement(movementEdge, speed, newPosition, train->getIdx());
}

bool MoveAgent::checkForDestination(Node *node, PathSearchPreferences prefs) {
    bool isValidDestination = false;
    if (prefs.isMovingToSpecificNode) {
        isValidDestination = node->getPointIdx() == prefs.destination->getPointIdx();
    } else {
        if (node->getType() == prefs.buildingType) {
            if (prefs.buildingType == 1) {
                isValidDestination = ((Town *) node)->isMine();
            } else if (prefs.buildingType == 2) {
                isValidDestination = (((Market *) node)->getProduct() > 0)
                        || (((Market *) node)->getReplenishment() > 0);
            } else if (prefs.buildingType == 3) {
                isValidDestination = (((Storage *) node)->getArmor() > 0)
                        || (((Storage *) node)->getReplenishment() > 0);
            }
        }
    }
    return isValidDestination;
}

bool MoveAgent::checkForTransit(Node *node, PathSearchPreferences prefs) {
    bool isValidTransit = true;
    uint32_t destinationBuildingType = prefs.buildingType;
    if (prefs.isMovingToSpecificNode) {
        destinationBuildingType = prefs.destination->getType();
    }
    if (destinationBuildingType == 2 && node->getType() == 3) {
        isValidTransit = (((Storage *) node)->getArmor() == 0)
                && (((Storage *) node)->getReplenishment() == 0);
    } else if (destinationBuildingType == 3 && node->getType() == 2) {
        isValidTransit = (((Market *) node)->getProduct() == 0)
                && (((Market *) node)->getReplenishment() == 0);
    }
    return isValidTransit;
}

bool MoveAgent::checkForSelfTrainsCollision(TrainMovement movement,
                                            Hometown* home,
                                            Train* currentTrain) {
    Node* potentialCollisionNode;
    for (auto train : home->getHometownTrains()) {
        if (train->getIdx() != currentTrain->getIdx()) {
            potentialCollisionNode = TrainsAgent::getTrainNode(train);
            if (potentialCollisionNode) {
                if (potentialCollisionNode->getPointIdx() != home->getPointIdx()) {
                    if ((potentialCollisionNode->getPointIdx()
                         == movement.line->getFirstNode()->getPointIdx()
                         && movement.newPosition == 0)
                        || (potentialCollisionNode->getPointIdx()
                            == movement.line->getSecondNode()->getPointIdx()
                            && movement.newPosition == movement.line->getLength())) {
                        return false;
                    }
                }
            } else {
                if (movement.line->getLineIdx() == train->getLineIdx()
                    && movement.newPosition == train->getPosition()) {
                    return false;
                }
            }
        }
    }
    return true;
}

std::vector<TrainMovement> MoveAgent::moveAll(std::vector<Node*>& graph,
                        const std::map<int32_t, uint32_t>& pointIdxCompression,
                        Hometown* home) {
    std::map<uint32_t, uint32_t> currentPositions;
    std::map<uint32_t, const Edge*> currentLines;

    std::vector<TrainMovement> movements;
    uint32_t building;
    for (int i = 0; i < 3; i++) {
        Train* train = home->getHometownTrains()[i];
        currentPositions.insert(std::make_pair(train->getIdx(), train->getPosition()));
        currentLines.insert(std::make_pair(train->getIdx(), train->getEdge()));

        if (i == 0) {
            building = 3;
        } else {
            building = 2;
        }
        TrainMovement movement = move(graph, pointIdxCompression,
                                      train, building, home);
        movements.push_back(movement);
        train->setPosition(movement.newPosition);
        train->setAttachedEdge(const_cast<Edge *>(movement.line));
    }

    // return back to positions
    for (int i = 0; i < 3; i++) {
        Train* train = home->getHometownTrains()[i];
        train->setPosition(currentPositions.at(train->getIdx()));
        train->setAttachedEdge(const_cast<Edge *>(currentLines.at(train->getIdx())));
    }

    return movements;
}

TrainMovement::TrainMovement(const Edge* line, int32_t speed, uint32_t newPos, uint32_t trainIdx)
                                                            : line(line)
                                                            , speed(speed)
                                                            , trainIdx(trainIdx)
                                                            , newPosition(newPos) {}

PathSearchPreferences::PathSearchPreferences(bool isMovingToSpecificNode, int32_t buildingType, Node *destination)
        : isMovingToSpecificNode(isMovingToSpecificNode), buildingType(buildingType), destination(destination) {}

NextNode::NextNode(Node *node, uint32_t totalPathLength) : node(node), totalPathLength(totalPathLength) {}

NextNode::NextNode() : node(nullptr), totalPathLength(0) {}