#include "GameMap.h"
#include <Pathfinding/RandomGridGenerator.h>
#include <Pathfinding/Grid.h>
#include <SFML/Graphics.hpp>
#include "Camera.h"

GameMap::GameMap(): sizeX(1), sizeY(1), grid(1,1) {}

GameMap::GameMap(int sizeX, int sizeY)
: sizeX(sizeX), sizeY(sizeY), grid(sizeX, sizeY) {
    RandomGridGenerator::generateAutomataGrid(grid, 0.45f, 5, .35f);
}

void GameMap::draw(sf::RenderWindow& window, const Camera& camera) {
    const int width = 10;


    sf::RectangleShape shape;
    shape.setFillColor(sf::Color::Green);
    shape.setSize(sf::Vector2f(width, width));

    for (size_t y=0; y<sizeY; ++y) {
        for (size_t x=0; x<sizeX; ++x) {
            if (grid.blocked[y][x]) {
                int drawX = x * width;
                int drawY = y * width;
                camera.absToRel(drawX, drawY);
                shape.setPosition(drawX, drawY);
                window.draw(shape);
            }
        }
    }

}