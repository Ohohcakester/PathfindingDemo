#include "PathFollower.h"
#include "GameMap.h"

void PathFollower::followPath(const GameMap& gameMap) {
    float remainingDistance = speed;

    while (true) {
        // Case 0: Reached end of path. Break loop.
        if (remainingPath.size() <= 0) break;
        const GridVertex& target = remainingPath.back();
        int tx = target.x;
        int ty = target.y;
        gameMap.gridToActual(tx, ty);

        float dx = tx - x;
        float dy = ty - y;
        float distanceToNext = sqrt(dx*dx+dy*dy);

        if (remainingDistance < distanceToNext) {
            // Case 1: Haven't reached next destination. Break loop.
            float ratio = remainingDistance / distanceToNext;
            x += dx * ratio;
            y += dy * ratio;
            break;
        } else {
            // Case 2: Reached destination. Continue loop.
            x = tx;
            y = ty;
            remainingDistance -= distanceToNext;
            remainingPath.pop_back();
        }
    }
}



