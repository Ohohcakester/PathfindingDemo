#include "ExplorerBot.h"
#include "RetrieverBot.h"
#include "Camera.h"
#include "GameVariables.h"
#include "GameMap.h"
#include "InputState.h"

ExplorerBot::ExplorerBot(int x, int y) {
    this->x = x;
    this->y = y;
    this->speed = 4;

    shape.setFillColor(sf::Color(255,127,0));
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
}

void ExplorerBot::update(const InputState& key, GameVariables& data) {
    if (true || key.space) {
        retrieveRandomMineral(data);
    }

    if (key.leftmouse_click) {
        int destX = key.leftMouseClickX;
        int destY = key.leftMouseClickY;
        data.camera->relToAbs(destX, destY);
        goToPosition(destX, destY, *data.gameMap);
    }
    followPath(*data.gameMap);
}

void ExplorerBot::retrieveRandomMineral(GameVariables& data) {
    bool hasUnmarkedMineral;
    auto mineralId = markedMinerals.getRandomUnmarkedMineral(hasUnmarkedMineral, data.mineralManager);
    if (hasUnmarkedMineral) {
        markedMinerals.markMineral(mineralId);
        GameObjectRef minRef = data.getObjectReference(mineralId);
        GameObjectRef myRef = data.getObjectReference(this->getId());
        auto botId = data.createObject(new RetrieverBot(x, y, myRef));
        (data.getGameObject<RetrieverBot>(botId))->goPickUp(minRef, data);
    }
}

void ExplorerBot::draw(sf::RenderWindow& window, const Camera& camera) {
    int drawX = x, drawY = y;
    camera.absToRel(drawX, drawY);
    shape.setPosition(drawX, drawY);
    window.draw(shape);
}

