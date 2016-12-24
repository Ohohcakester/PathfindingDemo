#include <SFML/Graphics.hpp>
#include "Game.h"
#include "InputState.h"
#include "GameVariables.h"
#include "Camera.h"
#include "GameVariables.h"
#include "GameMap.h"

Game::Game() {

}

Game::~Game() {
    if (gameVariables != nullptr) delete gameVariables;
}

void Game::initialise() {
    if (gameVariables != nullptr) {
        delete gameVariables;
        gameVariables = nullptr;
    }
    gameVariables = new GameVariables();
}

void Game::update(InputState& key) {
    if (gameVariables == nullptr) return;
    GameVariables& data = *gameVariables;
    Camera& camera = *data.camera;

    camera.update(key);
}

void Game::draw(sf::RenderWindow& window) {
    const GameVariables& data = *gameVariables;
    const Camera& camera = *data.camera;

    data.gameMap->draw(window, camera);
}