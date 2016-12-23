#include "PathFollower.h"

void PathFollower::followPath() {
    float remainingDistance = speed;

    while (true) {
        // Case 0: Reached end of path. Break loop.
        if (remainingPath.size() <= 0) break;
        const GridVertex& target = remainingPath.back();
        float dx = target.x - x;
        float dy = target.y - y;
        float distanceToNext = sqrt(dx*dx+dy*dy);

        if (remainingDistance < distanceToNext) {
            // Case 1: Haven't reached next destination. Break loop.
            float ratio = remainingDistance / distanceToNext;
            x += dx * ratio;
            y += dx * ratio;
            break;
        } else {
            // Case 2: Reached destination. Continue loop.
            dx = target.x;
            dy = target.y;
            remainingDistance -= distanceToNext;
            remainingPath.pop_back();
        }
    }
}



