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


void ExplorerBot::goToPosition(int destX, int destY, const GameMap& gameMap) {
    gameMap.getNearestGridCoordinate(destX, destY);
    int currX = x;
    int currY = y;
    gameMap.getNearestGridCoordinate(currX, currY);

    // Compute path in reverse.
    Path path = gameMap.getShortestPath(destX, destY, currX, currY);
    std::cout << currX << " " << currY << " "<< destX << " " << destY << " " << path.size() << std::endl;
    remainingPath.swap(path);
    // last vertex in path should be (currX,currY). Don't need it.
    if (remainingPath.size() > 0) remainingPath.pop_back();
}

void ExplorerBot::draw(sf::RenderWindow& window, const Camera& camera) {
    int drawX = x, drawY = y;
    camera.absToRel(drawX, drawY);
    shape.setPosition(drawX, drawY);
    window.draw(shape);
}

