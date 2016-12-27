#ifndef _MINERAL_MANAGER_H_
#define _MINERAL_MANAGER_H_

#include "DataTypes.h"
#include <vector>
class GameVariables;
class InputState;

class MineralManager {

    std::vector<GameObjectID> minerals;

public:
    GameObjectID getRandomMineral();
    void removeMineral(GameObjectID id);
    void initialise(GameVariables& data);
    void update(const InputState& key, GameVariables& data);
};

#endif