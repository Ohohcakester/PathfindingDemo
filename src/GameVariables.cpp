#include "GameVariables.h"
#include "GameMap.h"
#include "Camera.h"

GameVariables::~GameVariables() {
    delete gameMap;
    delete camera;
}

GameVariables::GameVariables() {
    gameMap = new GameMap(500,500);
    camera = new Camera();
}

