#include "GameMap.h"
#include <Pathfinding/RandomGridGenerator.h>
#include <Pathfinding/Grid.h>
#include <Pathfinding/ENLSVGEdgeAlgorithm.h>
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "GameGlobals.h"

GameMap::GameMap(): sizeX(1), sizeY(1), grid(1,1) {}

GameMap::GameMap(int sizeX, int sizeY)
: sizeX(sizeX), sizeY(sizeY), grid(sizeX, sizeY) {
    RandomGridGenerator::generateAutomataGrid(grid, 0.45f, 5, .35f);
    algo.reset(new ENLSVG::Algorithm(grid));
    memory.reset(new ENLSVG::Memory(algo->graph));
}

Path GameMap::getShortestPath(int sx, int sy, int ex, int ey) const {
    if (sx < 0 || sy < 0 || sx > sizeX || sy > sizeY) return Path();
    return algo->computePath(*memory, sx, sy, ex, ey);
}

void GameMap::draw(sf::RenderWindow& window, const Camera& camera) const {

    sf::RectangleShape shape;
    shape.setFillColor(sf::Color::Green);
    shape.setSize(sf::Vector2f(tileSize, tileSize));

    int x1 = 0, y1 = RES_Y, x2 = RES_X, y2 = 0;
    camera.relToAbs(x1, y1);
    camera.relToAbs(x2, y2);
    x1 = std::max(0, x1/tileSize);
    y1 = std::max(0, y1/tileSize);
    x2 = std::min(sizeX, x2/tileSize + 1);
    y2 = std::min(sizeY, y2/tileSize + 1);

    for (size_t y=y1; y<y2; ++y) {
        for (size_t x=x1; x<x2; ++x) {
            if (grid.blocked[y][x]) {
                int drawX = x * tileSize;
                int drawY = (y+1) * tileSize;
                camera.absToRel(drawX, drawY);
                shape.setPosition(drawX, drawY);
                window.draw(shape);
            }
        }
    }

}