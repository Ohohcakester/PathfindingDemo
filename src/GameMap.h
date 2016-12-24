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
};

#endif