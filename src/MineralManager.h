#ifndef _MINERAL_MANAGER_H_
#define _MINERAL_MANAGER_H_

#include "DataTypes.h"
#include <vector>
class GameVariables;
class InputState;

class MineralManager {
    std::vector<GameObjectID> minerals;
public:
    inline const std::vector<GameObjectID>& getMinerals() const {return minerals;}

    GameObjectID getRandomMineral();
    void removeMineral(GameObjectID id, GameVariables& data);
    void initialise(GameVariables& data);
    void update(const InputState& key, GameVariables& data);
};

#endif