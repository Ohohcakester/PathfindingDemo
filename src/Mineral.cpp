#include "Mineral.h"
#include "GameMap.h"
#include "Camera.h"

Mineral::Mineral(int gridX, int gridY, const GameMap& gameMap)
: gridX(gridX), gridY(gridY) {
    int px = gridX, py = gridY;
    gameMap.gridToActual(px, py);
    this->x = px;
    this->y = py;
    
    const int width = 12;
    const int height = 10;

    shape.setFillColor(sf::Color::Blue);
    shape.setSize(sf::Vector2f(width, height));
    shape.setOrigin(width/2, height/2);
}

void Mineral::update(const InputState& key, GameVariables& data) {

}

void Mineral::draw(sf::RenderWindow& window, const Camera& camera) {
    int drawX = x, drawY = y;
    camera.absToRel(drawX, drawY);
    shape.setPosition(drawX, drawY);
    window.draw(shape);
}

