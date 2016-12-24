#ifndef _GAME_VARIABLES_H_
#define _GAME_VARIABLES_H_

#include "GameMap.h"
#include "Camera.h"
#include <memory>
class GameMap;
class Camera;

class GameVariables {
public:
    std::unique_ptr<GameMap> gameMap;
    std::unique_ptr<Camera> camera;

    GameVariables();
};

#endif