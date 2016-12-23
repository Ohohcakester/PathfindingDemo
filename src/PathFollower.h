#ifndef _PATH_FOLLOWER_H_
#define _PATH_FOLLOWER_H_

#include "IGameObject.h"
#include "Pathfinding/PathfindingDataTypes.h"
#include <vector>

class PathFollower: public IGameObject {
public:
    float speed;
    // Vertices of remainingPath are specified in reverse.
    std::vector<GridVertex> remainingPath;

    void followPath();
};


#endif