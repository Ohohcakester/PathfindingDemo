#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <Pathfinding/Grid.h>
#include <Pathfinding/PathfindingDataTypes.h>
#include <Pathfinding/ENLSVGEdgeAlgorithm.h>
#include <memory>
namespace sf {
    class RenderWindow;
}
class Camera;

class GameMap {
public:
    const int sizeX;
    const int sizeY;
    const int tileSize = 10;
    Grid grid;
    std::unique_ptr<ENLSVG::Algorithm> algo;
    std::unique_ptr<ENLSVG::Memory> memory;

    GameMap();
    GameMap(int sizeX, int sizeY);
    void draw(sf::RenderWindow& window, const Camera& camera) const;

    Path getShortestPath(int sx, int sy, int ex, int ey) const;

    inline void nearestGridCoordinate(int& cx, int& cy) {
        cx = (cx + tileSize/2) / tileSize;
        cy = (cy + tileSize/2) / tileSize;
    }

    inline void gridToActual(int& cx, int& cy) {
        cx *= tileSize;
        cy *= tileSize;
    }
};

#endif