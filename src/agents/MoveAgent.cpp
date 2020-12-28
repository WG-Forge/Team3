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
        && isSafeToLeaveNode(movement, home, train)
        && canEnterHomeTown(home, train, movement)) {
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
                        Hometown* home, uint32_t refugeesCount) {
    std::map<uint32_t, uint32_t> currentPositions;
    std::map<uint32_t, const Edge*> currentLines;

    std::vector<TrainMovement> movements;
    uint32_t building;

    for (auto train : home->getHometownTrains()) {
        currentPositions.insert(std::make_pair(train->getIdx(), train->getPosition()));
        currentLines.insert(std::make_pair(train->getIdx(), train->getEdge()));

        changeStrategy(train, home, refugeesCount);
        building = getBuildingType(trainStrategies[train->getIdx()]);

        TrainMovement movement = move(graph, pointIdxCompression,
                                      train, building, home);
        movements.push_back(movement);
        train->setPosition(movement.newPosition);
        train->setAttachedEdge(const_cast<Edge *>(movement.line));
    }

    // return back to positions
    for (auto train : home->getHometownTrains()) {
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

bool MoveAgent::canEnterHomeTown(Hometown* home, Train* train, TrainMovement movement) {
    bool canEnterHomeTown = true;
    if (trainStrategies[train->getIdx()] == MARKET_PREPARE
        && isNextHome(home, movement)) {
        canEnterHomeTown = false;
    }
    return canEnterHomeTown;
}

bool MoveAgent::isNextHome(Hometown* home, TrainMovement movement) {
    int32_t firstNode = movement.line->getFirstNode()->getPointIdx();
    int32_t secondNode = movement.line->getSecondNode()->getPointIdx();
    bool isNextHome = (firstNode == home->getPointIdx()
                       && movement.newPosition == 0)
                      || (secondNode == home->getPointIdx()
                          && movement.newPosition == movement.line->getLength());
    return isNextHome;
}

bool MoveAgent::areAnyTrainsBeforeHome(Hometown* home, Train* curTrain, TrainMovement movement) {

    for (auto train : home->getHometownTrains()) {
        if (train->getIdx() != curTrain->getIdx()
                && (train->getEdge()->getLineIdx() == movement.line->getLineIdx()
                || (TrainsAgent::getTrainNode(train)
                && TrainsAgent::getTrainNode(train)->getPointIdx() == home->getPointIdx()))) {
            return true;
        }
    }
    return false;
}

bool MoveAgent::isTownOverProduct(TrainMovement movement, Hometown *home, Train *currentTrain) {
    int32_t firstNode = movement.line->getFirstNode()->getPointIdx();
    int32_t secondNode = movement.line->getSecondNode()->getPointIdx();
    bool isNextNodeHome = (firstNode == home->getPointIdx()
                           && movement.speed == -1)
                          || (secondNode == home->getPointIdx()
                              && movement.speed == 1);
    if (isNextNodeHome && TrainsAgent::getTrainNode(currentTrain)
            && TrainsAgent::getTrainNode(currentTrain)->getPointIdx() != home->getPointIdx()
            && currentTrain->getGoodsType() == Train::GoodsType::PRODUCTS) {
        if (!areAnyTrainsBeforeHome(home, currentTrain, movement)) {
            int freeSpace = home->getProductCapacity() - home->getProduct()
                            + home->getPopulation() * movement.line->getLength();
            return freeSpace <= currentTrain->getGoods();
        } else {
            return true;
        }
    } else {
        return false;
    }
}

bool MoveAgent::isSafeToLeaveNode(TrainMovement movement, Hometown *home, Train *currentTrain) {
    Node* curNode = TrainsAgent::getTrainNode(currentTrain);
    if (curNode) {
        Node* nextNode = curNode->getPointIdx() == movement.line->getFirstNode()->getPointIdx()
                ? movement.line->getSecondNode()
                : movement.line->getFirstNode();

        for (auto train : home->getHometownTrains()) {
            // on same line
            if ((TrainsAgent::getTrainNode(train) == nullptr
                || (TrainsAgent::getTrainNode(train)->getPointIdx() != curNode->getPointIdx()
                        && TrainsAgent::getTrainNode(train)->getPointIdx() != home->getPointIdx()))
                && train->getIdx() != currentTrain->getIdx()
                && train->getLineIdx() == movement.line->getLineIdx()) {
                return false;
            }

            // on way to nextNode
            if (train->getEdge()->getLineIdx() != movement.line->getLineIdx()
                    && nextNode->getPointIdx() != home->getPointIdx()) {
                if (train->getEdge()->getFirstNode()->getPointIdx() == nextNode->getPointIdx()
                    && train->getSpeed() == -1) {
                    return false;
                } else if (train->getEdge()->getSecondNode()->getPointIdx() == nextNode->getPointIdx()
                           && train->getSpeed() == 1) {
                    return false;
                }
            }
        }
    }
    return true;
}

void MoveAgent::changeStrategy(Train* currentTrain, Hometown* home, uint32_t refugeesCount) {
    if (trainStrategies.empty()) {
        for (auto train : home->getHometownTrains()) {
            trainStrategies.insert(std::make_pair(train->getIdx(), STORAGE_START));
        }
    }

    Node* curNode = TrainsAgent::getTrainNode(currentTrain);
    switch (trainStrategies.at(currentTrain->getIdx())) {
        case STORAGE_START:
            if (curNode == nullptr || curNode->getPointIdx() != home->getPointIdx()) {
                trainStrategies[currentTrain->getIdx()] = STORAGE_IN_PROC;
            }
            break;
        case STORAGE_IN_PROC:
            if (curNode && curNode->getPointIdx() == home->getPointIdx()) {
                trainStrategies[currentTrain->getIdx()] = MARKET_PREPARE;
            }
            break;
        case MARKET_PREPARE:
            if (isAbleToKeepSettlers(home, refugeesCount)
                    || isAnyoneStillOnArmor(home)) {
                trainStrategies[currentTrain->getIdx()] = MARKET;
            }
            break;
        case MARKET:
            if (!isAbleToKeepSettlers(home, refugeesCount)
                    && !isAnyoneStillOnArmor(home)) {
                trainStrategies[currentTrain->getIdx()] = MARKET_PREPARE;
            }
            break;
    }
}

uint32_t MoveAgent::getBuildingType(Strategy strategy) {
    uint32_t building;
    switch (strategy) {
        case STORAGE_START:
            building = 3;
            break;
        case STORAGE_IN_PROC:
            building = 3;
            break;
        case MARKET_PREPARE:
            building = 2;
            break;
        case MARKET:
            building = 2;
            break;
    }
    return building;
}

bool MoveAgent::isAbleToKeepSettlers(Hometown *home, uint32_t refugeesCount) {
    float totalCapacity = 0;
    for (auto train : home->getHometownTrains()) {
        totalCapacity += train->getGoodsCapacity();
    }
    float maxPopulation = totalCapacity / marketCycleLen;
    int settlersEndGame = home->getPopulation() + (maxRefugeesCount - refugeesCount);
    return settlersEndGame < maxPopulation;
}

bool MoveAgent::isAnyoneStillOnArmor(Hometown *home) {
    for (auto strategy : trainStrategies) {
        if (strategy.second == STORAGE_START || strategy.second == STORAGE_IN_PROC) {
            return true;
        }
    }
    return false;
}

TrainMovement::TrainMovement(const Edge* line, int32_t speed, uint32_t newPos, uint32_t trainIdx)
                                                            : line(line)
                                                            , speed(speed)
                                                            , trainIdx(trainIdx)
                                                            , newPosition(newPos) {}
