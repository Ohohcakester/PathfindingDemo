#include "GameMap.h"
#include <Pathfinding/RandomGridGenerator.h>
#include <Pathfinding/Grid.h>
#include <Pathfinding/ENLSVGEdgeAlgorithm.h>
#include <SFML/Graphics.hpp>
#include "Camera.h"

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

    for (size_t y=0; y<sizeY; ++y) {
        for (size_t x=0; x<sizeX; ++x) {
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