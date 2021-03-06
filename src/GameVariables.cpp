#include "GameVariables.h"
#include "GameMap.h"
#include "Camera.h"
#include "IGameObject.h"

GameVariables::GameVariables() {
    gameMap.reset(new GameMap(1000,1000));
    camera.reset(new Camera());
}

GameVariables::~GameVariables() {
    for (size_t i=0; i<gameObjects.size(); ++i) {
        delete gameObjects[i];
    }
    gameObjects.clear();
}

