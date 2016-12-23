#include "GameVariables.h"
#include "GameMap.h"

GameVariables::~GameVariables() {
    delete gameMap;
}

GameVariables::GameVariables() {
    gameMap = new GameMap(500,500);

}

