#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <SFML/Graphics.hpp>
#include <Pathfinding/Grid.h>
#include <Pathfinding/PathfindingDataTypes.h>
#include <Pathfinding/ENLSVGEdgeAlgorithm.h>
#include <memory>
#include "RandomNumberGenerator.h"
class Camera;

class GameMap {
public:
    const int sizeX;
    const int sizeY;
    const int tileSize = 5;
    Grid grid;
    std::vector<GridVertex> coordinateList;

private:
    std::unique_ptr<ENLSVG::Algorithm> algo;
    std::unique_ptr<ENLSVG::Memory> memory;

    sf::Sprite mapSprite;
    sf::Texture mapTexture;

public:
    GameMap();
    GameMap(int sizeX, int sizeY);
    void draw(sf::RenderWindow& window, const Camera& camera);

    Path getShortestPath(int sx, int sy, int ex, int ey) const;

    inline void getNearestGridCoordinate(int& cx, int& cy) const {
        cx = (cx + tileSize/2) / tileSize;
        cy = (cy + tileSize/2) / tileSize;
    }

    inline void gridToActual(int& cx, int& cy) const {
        cx *= tileSize;
        cy *= tileSize;
    }

    inline GridVertex getRandomOpenCoordinate() const {
        int index = global_rng.index(coordinateList.size());
        return coordinateList[index];
    }

    inline bool lineOfSight(int sx, int sy, int ex, int ey) const {
        return grid.lineOfSight(sx, sy, ex, ey);
    }

private:
    void generateSprite();
    void isolateLargestConnectedComponent();
    void blockUpComponent(const std::vector<GridVertex>& component);
};

#endif