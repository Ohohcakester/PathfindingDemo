#ifndef _MARKED_MINERALS_H_
#define _MARKED_MINERALS_H_

#include "DataTypes.h"
#include <unordered_set>
class MineralManager;

class MarkedMinerals {
    std::unordered_set<GameObjectID> minerals;

public:
    GameObjectID getRandomUnmarkedMineral(bool& success, const MineralManager& mineralManager);
    inline void markMineral(GameObjectID id) {
        minerals.insert(id);
    }
    inline void unmarkMineral(GameObjectID id) {
        minerals.erase(id);
    }
};

#endif