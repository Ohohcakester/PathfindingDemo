#ifndef _GAME_VARIABLES_H_
#define _GAME_VARIABLES_H_

class GameMap;
class Camera;

class GameVariables {
public:
    GameMap* gameMap;
    Camera* camera;

    GameVariables();
    ~GameVariables();
};

#endif