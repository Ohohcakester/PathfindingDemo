#ifndef _PATH_FOLLOWER_H_
#define _PATH_FOLLOWER_H_

#include "IGameObject.h"
#include "GameMap.h"
#include "Pathfinding/PathfindingDataTypes.h"
#include <vector>

class PathFollower: public IGameObject {
protected:
    float speed = 0;
    // Vertices of remainingPath are specified in reverse.
    std::vector<Pathfinding::GridVertex> remainingPath;

    virtual ~PathFollower() {}
    void followPath(const GameMap& gameMap);
    void goToCoordinate(int destX, int destY, const GameMap& gameMap);
    void goToPosition(int destX, int destY, const GameMap& gameMap);

public:
    inline bool stoppedMoving() const {return remainingPath.size() == 0;}

    inline bool reachedDestination(Pathfinding::GridVertex destination, const GameMap& gameMap) const {
        int px = x, py = y;
        gameMap.getNearestGridCoordinate(px, py);
        return (px == destination.x && py == destination.y);
    }

    inline bool stoppedAndReachedDestination(Pathfinding::GridVertex destination, const GameMap& gameMap) const {
        return stoppedMoving() && reachedDestination(destination, gameMap);
    }
};


#endif