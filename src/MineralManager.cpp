#include "MineralManager.h"
#include "GameVariables.h"
#include "GameMap.h"
#include "Mineral.h"
#include "RandomNumberGenerator.h"
#include <stdlib.h>

GameObjectID MineralManager::getRandomMineral() {
    int nMinerals = minerals.size();
    size_t index = global_rng.index(nMinerals);
    return minerals[index];
}

void MineralManager::removeMineral(GameObjectID id, GameVariables& data) {
    // O(n). I think it's ok because this is not called often.
    auto itr = std::find(minerals.begin(), minerals.end(), id);
    if (itr != minerals.end()) {
        minerals.erase(itr);
    }

    IGameObject* mineral = data.getGameObject(id);
    mineral->destroy();
}

void MineralManager::initialise(GameVariables& data) {

}

void MineralManager::update(const InputState& key, GameVariables& data) {
    const int maxMinerals = 100;

    if (data.frame%120 == 0) {
        if (minerals.size() < maxMinerals) {
            GridVertex pos = data.gameMap->getRandomOpenCoordinate();
            GameObjectID id = data.createObject(new Mineral(pos.x, pos.y, *data.gameMap));
            minerals.push_back(id);
        }
    }
}

