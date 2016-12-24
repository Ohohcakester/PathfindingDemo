#include "GameVariables.h"
#include "GameMap.h"
#include "Camera.h"

GameVariables::GameVariables() {
    gameMap.reset(new GameMap(100,80));
    camera.reset(new Camera());
}

