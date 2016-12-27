#include "GameManager.h"
#include "GameVariables.h"
#include "InputState.h"
#include "ExplorerBot.h"
#include "Mineral.h"

void GameManager::initialise(GameVariables& data) const {
    data.createObject(new ExplorerBot(350,350));

    data.frame = 0;
}


void GameManager::update(const InputState& key, GameVariables& data) const {
    data.mineralManager.update(key, data);

    ++data.frame;
}