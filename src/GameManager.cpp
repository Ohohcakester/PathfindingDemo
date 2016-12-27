#include "GameManager.h"
#include "GameVariables.h"
#include "InputState.h"
#include "ExplorerBot.h"
#include "Mineral.h"
#include "GameMap.h"

void GameManager::initialise(GameVariables& data) const {
    {
        GridVertex coord = data.gameMap->getRandomOpenCoordinate();
        int spawnX = coord.x, spawnY = coord.y;
        data.gameMap->gridToActual(spawnX, spawnY);
        data.createObject(new ExplorerBot(spawnX,spawnY));
    }

    data.frame = 0;
}


void GameManager::update(const InputState& key, GameVariables& data) const {
    data.mineralManager.update(key, data);

    ++data.frame;
}