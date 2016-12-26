#ifndef _PATH_FOLLOWER_H_
#define _PATH_FOLLOWER_H_

#include "IGameObject.h"
#include "Pathfinding/PathfindingDataTypes.h"
#include <vector>
class GameMap;

class PathFollower: public IGameObject {
protected:
    float speed = 0;
    // Vertices of remainingPath are specified in reverse.
    std::vector<GridVertex> remainingPath;

    virtual ~PathFollower() {}
    void followPath(const GameMap& gameMap);
    void goToCoordinate(int destX, int destY, const GameMap& gameMap);
    void goToPosition(int destX, int destY, const GameMap& gameMap);
};


#endif