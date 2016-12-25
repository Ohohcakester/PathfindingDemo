#include "ExplorerBot.h"
#include "Camera.h"
#include "GameVariables.h"
#include "GameMap.h"
#include "InputState.h"

ExplorerBot::ExplorerBot(int x, int y) {
    this->x = x;
    this->y = y;
    this->speed = 5;

    shape.setFillColor(sf::Color::Yellow);
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
}

void ExplorerBot::update(const InputState& key, GameVariables& data) {
    if (key.leftmouse_click) {
        int destX = key.leftMouseClickX;
        int destY = key.leftMouseClickY;
        data.camera->relToAbs(destX, destY);
        goToPosition(destX, destY, *data.gameMap);
    }
    followPath(*data.gameMap);
}

void ExplorerBot::draw(sf::RenderWindow& window, const Camera& camera) {
    int drawX = x, drawY = y;
    camera.absToRel(drawX, drawY);
    shape.setPosition(drawX, drawY);
    window.draw(shape);
}

