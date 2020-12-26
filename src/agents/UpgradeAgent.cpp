#include "UpgradeAgent.h"

std::vector<int32_t> UpgradeAgent::upgradeTrains(Hometown *home, int hijackersCount) {
    if (!isFirstUpgradeMade) {
        isFirstUpgradeMade = true;
        return firstUpgrade(home);
    }
    std::vector<int32_t> trainsToUpgrade;

    int hijackersRemain = maxHijackers - hijackersCount;
    int availableArmor = home->getArmor() - hijackersRemain;
    Train* looserTrain = nullptr; // with first level

    for (auto train : home->getHometownTrains()) {
        Node* trainNode = TrainsAgent::getTrainNode(train);
        if (trainNode && trainNode->getPointIdx() == home->getPointIdx() && train->getLevel() != 3) {
            if (train->getLevel() == 2 && availableArmor >= train->getNextLevelPrice()) {
                trainsToUpgrade.push_back(train->getIdx());
                availableArmor -= train->getNextLevelPrice();
            } else {
                looserTrain = train;
            }
        }
    }

    if (looserTrain && availableArmor >= looserTrain->getNextLevelPrice()) {
        trainsToUpgrade.push_back(looserTrain->getIdx());
        availableArmor -= looserTrain->getNextLevelPrice();

        if (availableArmor >= secondLevelPrice) {
            trainsToUpgrade.push_back(looserTrain->getIdx());
            availableArmor -= looserTrain->getNextLevelPrice();
        }
    }
    return trainsToUpgrade;
}

std::vector<int32_t> UpgradeAgent::firstUpgrade(Hometown *home) {
    auto trains = home->getHometownTrains();
    return std::vector<int32_t> {trains[0]->getIdx(),
                                 trains[1]->getIdx(),
                                 trains[2]->getIdx()};
}

UpgradeAgent::UpgradeAgent() : isFirstUpgradeMade(false) {}
