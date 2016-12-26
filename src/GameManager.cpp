#include "GameManager.h"
#include "GameVariables.h"
#include "InputState.h"
#include "ExplorerBot.h"

void GameManager::initialise(GameVariables& data) const {
    data.createObject(new ExplorerBot(350,350));
}


void GameManager::update(const InputState& key, GameVariables& data) const {

}