#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <Pathfinding/Grid.h>
namespace sf {
    class RenderWindow;
}
class Camera;

class GameMap {
public:
    const int sizeX;
    const int sizeY;
    Grid grid;

    GameMap();
    GameMap(int sizeX, int sizeY);
    void draw(sf::RenderWindow& window, const Camera& camera) const;
};

#endif