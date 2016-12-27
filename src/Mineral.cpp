#include "Mineral.h"
#include "GameMap.h"
#include "GameVariables.h"
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
    if (state == MineralState::carried) updateCarrierLocation(data);
}

void Mineral::draw(sf::RenderWindow& window, const Camera& camera) {
    int drawX, drawY;

    if (state == MineralState::carried) {
        drawX = lastCarrierX;
        drawY = lastCarrierY;
    } else {
        drawX = x;
        drawY = y;
    }

    camera.absToRel(drawX, drawY);
    shape.setPosition(drawX, drawY);
    window.draw(shape);
}

void Mineral::updateCarrierLocation(const GameVariables& data) {
    IGameObject* carrierObject = data.getGameObject(carrierRef);
    if (carrierObject == nullptr) {
        std::cout << "ERROR: MISSING CARRIER" << std::endl;
    }
    lastCarrierX = carrierObject->x;
    lastCarrierY = carrierObject->y;
}

void Mineral::pickUp(GameObjectID carrierId, const GameVariables& data) {
    carrierRef = data.getObjectReference(carrierId);
    state = MineralState::carried;
    updateCarrierLocation(data);
}

void Mineral::drop(int _gridX, int _gridY, const GameVariables& data) {
    this->gridX = _gridX;
    this->gridY = _gridY;
    int px = gridX, py = gridY;
    data.gameMap->gridToActual(px, py);
    this->x = px;
    this->y = py;

    state = MineralState::on_ground;
}

