#include "GameMap.h"
#include <Pathfinding/RandomGridGenerator.h>

GameMap::GameMap(): sizeX(1), sizeY(1), grid(1,1) {}

GameMap::GameMap(int sizeX, int sizeY)
: sizeX(sizeX), sizeY(sizeY), grid(sizeX, sizeY) {
    RandomGridGenerator::generateAutomataGrid(grid, 0.45f, 5, .35f);
}