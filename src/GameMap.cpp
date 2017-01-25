#include "GameMap.h"
#include <Pathfinding/RandomGridGenerator.h>
#include <Pathfinding/Grid.h>
#include <Pathfinding/ENLSVGAlgorithm.h>
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "GameGlobals.h"

GameMap::GameMap(): sizeX(1), sizeY(1), grid(1,1) {}

GameMap::GameMap(int sizeX, int sizeY)
: sizeX(sizeX), sizeY(sizeY), grid(sizeX, sizeY) {
    Pathfinding::RandomGridGenerator::generateAutomataGrid(grid, 0.37f, 5, .15f);
    isolateLargestConnectedComponent();
    algo.reset(new Pathfinding::ENLSVG::Algorithm(grid));
    memory.reset(new Pathfinding::ENLSVG::Memory(algo->graph));

    generateSprite();
}

void GameMap::isolateLargestConnectedComponent() {
    using Pathfinding::GridVertex;

    std::vector<std::vector<GridVertex>*> components;
    std::vector<std::vector<bool>> visited;
    visited.resize(sizeY+1);
    for (size_t y=0;y<=sizeY;++y) visited[y].resize(sizeX+1, false);

    for (size_t y=0;y<=sizeY;++y) {
        for (size_t x=0;x<=sizeX;++x) {
            if (visited[y][x]) continue;
            if (grid.isBlocked(x-1,y-1) || grid.isBlocked(x,y-1) ||
                grid.isBlocked(x-1,y) || grid.isBlocked(x,y)) continue;

            std::vector<GridVertex>* componentPtr = new std::vector<GridVertex>();
            std::vector<GridVertex>& component = *componentPtr;

            // BFS
            size_t index = 0;
            component.push_back(GridVertex(x,y));
            while (index < component.size()) {
                int cx = component[index].x;
                int cy = component[index].y;

                bool blockedUL = grid.isBlocked(cx-1,cy-1);
                bool blockedUR = grid.isBlocked(cx,cy-1);
                bool blockedBL = grid.isBlocked(cx-1,cy);
                bool blockedBR = grid.isBlocked(cx,cy);

                // UP
                if ((!blockedUL || !blockedUR) && (cy > 0 && !visited[cy-1][cx])) {
                    component.push_back(GridVertex(cx,cy-1));
                    visited[cy-1][cx] = true;
                }

                // DOWN
                if ((!blockedBL || !blockedBR) && (cy < sizeY-1 && !visited[cy+1][cx])) {
                    component.push_back(GridVertex(cx,cy+1));
                    visited[cy+1][cx] = true;
                }

                // LEFT
                if ((!blockedUL || !blockedBL) && (cx > 0 && !visited[cy][cx-1])) {
                    component.push_back(GridVertex(cx-1,cy));
                    visited[cy][cx-1] = true;
                }

                // RIGHT
                if ((!blockedUR || !blockedBR) && (cx < sizeX-1 && !visited[cy][cx+1])) {
                    component.push_back(GridVertex(cx+1,cy));
                    visited[cy][cx+1] = true;
                }

                ++index;
            }
            components.push_back(componentPtr);
        }
    }

    // Pick largest component.
    int maxSize = -1;
    int largestIndex = -1;
    for (size_t i=0; i<components.size(); ++i) {
        if ((int)components[i]->size() > maxSize) {
            largestIndex = i;
            maxSize = components[i]->size();
        }
    }

    coordinateList.clear();
    if (largestIndex != -1) coordinateList.swap(*components[largestIndex]);
    // Block up all the other components. components[largestIndex] should be enpty.
    for (size_t i=0; i<components.size(); ++i) {
        blockUpComponent(*components[i]);
    }

    for (size_t i=0; i<components.size(); ++i) {
        delete components[i];
    }
}

// Turns all tiles around the selected component into blocked tiles.
void GameMap::blockUpComponent(const std::vector<Pathfinding::GridVertex>& component) {
    for (size_t i=0; i<component.size(); ++i) {
        int cx = component[i].x;
        int cy = component[i].y;
        for (int y = cy-1; y<=cy; ++y) {
            for (int x = cx-1; x<=cx; ++x) {
                if (!grid.isBlocked(x,y)) grid.setBlocked(x, y, true);
            }
        }
    }
}

Pathfinding::Path GameMap::getShortestPath(int sx, int sy, int ex, int ey) const {
    if (sx < 0 || sy < 0 || sx > sizeX || sy > sizeY) return Pathfinding::Path();
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