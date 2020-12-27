#include "UpgradeAgent.h"

std::vector<int32_t> UpgradeAgent::upgradeTrains(Hometown *home, int hijackersCount) {
    std::vector<int32_t> trainsToUpgrade;

    int hijackersRemain = maxHijackers - hijackersCount;
    int availableArmor = home->getArmor() - hijackersRemain;
    std::vector<Train*> looserTrains; // with first level
    int countOfLevel1 = 0;

    for (auto train : home->getHometownTrains()) {
        if (train->getLevel() == 1) {
            countOfLevel1 += 1;
        }
        Node* trainNode = TrainsAgent::getTrainNode(train);
        if (trainNode && trainNode->getPointIdx() == home->getPointIdx() && train->getLevel() != 3) {
            if (train->getLevel() == 2 && availableArmor >= train->getNextLevelPrice()) {
                trainsToUpgrade.push_back(train->getIdx());
                availableArmor -= train->getNextLevelPrice();
            } else {
                looserTrains.push_back(train);
            }
        }
    }

    if (countOfLevel1 > 1) {
        availableArmor += hijackersRemain;
    }
    // all to second level (if possible)
    for (auto looserTrain : looserTrains) {
        if (looserTrain && availableArmor >= looserTrain->getNextLevelPrice()) {
            trainsToUpgrade.push_back(looserTrain->getIdx());
            availableArmor -= looserTrain->getNextLevelPrice();
        }
    }

    // all to third level (if possible)
    for (auto looserTrain : looserTrains) {
        if (availableArmor >= secondLevelPrice) {
            trainsToUpgrade.push_back(looserTrain->getIdx());
            availableArmor -= looserTrain->getNextLevelPrice();
        }
    }
    return trainsToUpgrade;
}

UpgradeAgent::UpgradeAgent() : isFirstUpgradeMade(false) {}
