#ifndef _GAME_VARIABLES_H_
#define _GAME_VARIABLES_H_

#include "GameMap.h"
#include "Camera.h"
#include <memory>
#include <vector>
class GameMap;
class Camera;
class IGameObject;

class GameVariables {
public:
    std::unique_ptr<GameMap> gameMap;
    std::unique_ptr<Camera> camera;
    std::vector<IGameObject*> gameObjects;

    GameVariables();
    ~GameVariables();
};

#endif