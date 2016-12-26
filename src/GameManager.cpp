#include "GameManager.h"
#include "GameVariables.h"
#include "InputState.h"
#include "ExplorerBot.h"
#include "Mineral.h"

void GameManager::initialise(GameVariables& data) const {
    data.createObject(new ExplorerBot(350,350));

    data.frame = 0;
    data.mineralCount = 0;
}


void GameManager::update(const InputState& key, GameVariables& data) const {
    const int maxMinerals = 100;

    if (data.frame%120 == 0) {
        if (data.mineralCount < maxMinerals) {
            GridVertex pos = data.gameMap->getRandomOpenCoordinate();
            data.createObject(new Mineral(pos.x, pos.y, *data.gameMap));
            ++data.mineralCount;
        }
    }

    ++data.frame;
}