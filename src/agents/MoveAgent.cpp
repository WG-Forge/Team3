#include <MoveAgent.h>

TrainMovement MoveAgent::move(std::vector<Node*>& graph,
                              const std::map<int32_t, uint32_t>& pointIdxCompression,
                              Train* train,
                              uint32_t building,
                              Hometown* home) {
    Node* newNode = getNextNodeCycles(graph, pointIdxCompression, train,
                         building, home->getPointIdx());
    TrainMovement movement = calcMovement(train, newNode);
    if (!isSelfTrainsCollisionOccurs(movement, home, train)
        && !isTownOverProduct(movement, home, train)
        && isSafeToLeaveNode(movement, home, train)) {
        return movement;
    } else {
        return TrainMovement(train->getEdge(), 0, train->getPosition(), train->getIdx());
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

bool MoveAgent::isSelfTrainsCollisionOccurs(TrainMovement movement,
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
                        return true;
                    }
                }
            } else {
                if (movement.line->getLineIdx() == train->getLineIdx()
                    && movement.newPosition == train->getPosition()) {
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<TrainMovement> MoveAgent::moveAll(std::vector<Node*>& graph,
                        const std::map<int32_t, uint32_t>& pointIdxCompression,
                        Hometown* home) {
    std::map<uint32_t, uint32_t> currentPositions;
    std::map<uint32_t, const Edge*> currentLines;

    std::vector<TrainMovement> movements;
    uint32_t building;
    for (int i = 0; i < 4; i++) {
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
    for (int i = 0; i < 4; i++) {
        Train* train = home->getHometownTrains()[i];
        train->setPosition(currentPositions.at(train->getIdx()));
        train->setAttachedEdge(const_cast<Edge *>(currentLines.at(train->getIdx())));
    }

    return movements;
}

Node* MoveAgent::getNextNodeCycles(std::vector<Node*>& graph,
                                   const std::map<int32_t, uint32_t> &pointIdxCompression,
                                   Train *train, int32_t buildingType, uint32_t homeIdx) {
    const std::vector<int> *cycle;
    if (train->getGoods() > 0 && train->getGoods() < train->getGoodsCapacity()) {
        return nullptr;
    }
    if (buildingType == 2) {
        for (int i = 0; i < marketCycles.size(); i++) {
            if (marketCycles[i][0] == homeIdx) {
                cycle = &marketCycles[i];
            }
        }
    } else {
        for (int i = 0; i < storageCycles.size(); i++) {
            if (storageCycles[i][0] == homeIdx) {
                cycle = &storageCycles[i];
            }
        }
    }

    int firstIdx = train->getEdge()->getFirstNode()->getPointIdx();
    int secondIdx = train->getEdge()->getSecondNode()->getPointIdx();

    int nextNodeIdx;
    for (int i = 0; i < cycle->size(); i++) {
        if (cycle->at(i) == firstIdx) {
            int nextPosition = getNextIndex(i, cycle->size());
            if (cycle->at(nextPosition) == secondIdx) {
                nextNodeIdx = secondIdx;
                if (train->getPosition() == train->getEdge()->getLength()) {
                    nextNodeIdx = cycle->at(getNextIndex(nextPosition, cycle->size()));
                }
            } else {
                nextNodeIdx = firstIdx;
                if (train->getPosition() == 0) {
                    nextNodeIdx = cycle->at(getNextIndex(i, cycle->size()));
                }
            }
            return graph.at(pointIdxCompression.at(nextNodeIdx));
        }
    }
    return nullptr;
}

int MoveAgent::getNextIndex(int currentIndex, int vectorSize) {
    int nextPosition = currentIndex+1;
    if (nextPosition >= vectorSize) {
        nextPosition = 0;
    }
    return nextPosition;
}

bool MoveAgent::isTownOverProduct(TrainMovement movement, Hometown *home, Train *currentTrain) {
    int32_t firstNode = currentTrain->getEdge()->getFirstNode()->getPointIdx();
    int32_t secondNode = currentTrain->getEdge()->getSecondNode()->getPointIdx();
    bool isNextHome = (firstNode == home->getPointIdx()
            && movement.newPosition == 0
            && movement.speed == -1)
            || (secondNode == home->getPointIdx()
            && movement.newPosition == movement.line->getLength()
            && movement.speed == 1);
    if (isNextHome && currentTrain->getGoodsType() == Train::GoodsType::PRODUCTS) {
        int freeSpace = home->getProductCapacity() - home->getProduct() + home->getPopulation();
        return freeSpace <= currentTrain->getGoods();
    } else {
        return false;
    }
}

bool MoveAgent::isSafeToLeaveNode(TrainMovement movement, Hometown *home, Train *currentTrain) {
    Node* curNode = TrainsAgent::getTrainNode(currentTrain);
    if (curNode) {
        for (auto train : home->getHometownTrains()) {
            if ((TrainsAgent::getTrainNode(train) == nullptr
                        || TrainsAgent::getTrainNode(train)->getPointIdx() != curNode->getPointIdx())
                && train->getIdx() != currentTrain->getIdx()
                && train->getLineIdx() == movement.line->getLineIdx()) {
                return false;
            }
        }
    }
    return true;
}

TrainMovement::TrainMovement(const Edge* line, int32_t speed, uint32_t newPos, uint32_t trainIdx)
                                                            : line(line)
                                                            , speed(speed)
                                                            , trainIdx(trainIdx)
                                                            , newPosition(newPos) {}
