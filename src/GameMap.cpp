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
    RandomGridGenerator::generateAutomataGrid(grid, 0.37f, 5, .1f);
    algo.reset(new ENLSVG::Algorithm(grid));
    memory.reset(new ENLSVG::Memory(algo->graph));

    generateSprite();
}

Path GameMap::getShortestPath(int sx, int sy, int ex, int ey) const {
    if (sx < 0 || sy < 0 || sx > sizeX || sy > sizeY) return Path();
    return algo->computePath(*memory, sx, sy, ex, ey);
}

void GameMap::generateSprite() {

    mapTexture.create(sizeX, sizeY);

    // * 4 because pixels have 4 components (RGBA)
    sf::Uint8* pixels = new sf::Uint8[sizeX * sizeY * 4];

    size_t base = 0;
    for (size_t y=sizeY-1; y<sizeY; --y) {
        for (size_t x=0; x<sizeX; ++x) {
            const bool blocked = grid.blocked[y][x];
            // Colour: Green.
            pixels[base++] = 0;
            pixels[base++] = blocked ? 255 : 0;
            pixels[base++] = 0;
            pixels[base++] = 255;
        }
    }

    mapTexture.update(pixels);
    delete[] pixels;
    mapSprite.setTexture(mapTexture);
    mapSprite.setOrigin(sf::Vector2f(0,sizeY));
}

void GameMap::draw(sf::RenderWindow& window, const Camera& camera) {
    mapSprite.setScale(sf::Vector2f(tileSize,tileSize));
    int baseX = 0, baseY = 0;
    camera.absToRel(baseX, baseY);
    mapSprite.setPosition(baseX, baseY);
    window.draw(mapSprite);

}