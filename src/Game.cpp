#include <SFML/Graphics.hpp>
#include "Game.h"
#include "InputState.h"
#include "GameVariables.h"
#include "Camera.h"
#include "GameVariables.h"
#include "GameMap.h"
#include "IGameObject.h"

Game::Game() {

}

void Game::initialise() {
    gameVariables.reset(new GameVariables());
    gameManager.initialise(*gameVariables);
}

void Game::update(InputState& key) {
    if (gameVariables == nullptr) return;
    GameVariables& data = *gameVariables;
    Camera& camera = *data.camera;
    std::vector<IGameObject*>& gameObjects = data.gameObjects;

    gameManager.update(key, data);

    camera.update(key);

    size_t nActive = 0;
    for (size_t i=0; i<gameObjects.size(); ++i) {
        if (gameObjects[i]->isActive()) {
            gameObjects[i]->update(key, data);
        } else {
            ++nActive;
        }
    }

    // less than half-full: reallocate gameObjects vector.
    if (nActive*2 <= gameObjects.size()) {
        data.reallocateGameObjectsArray(nActive);
    }
}

void Game::draw(sf::RenderWindow& window) {
    const GameVariables& data = *gameVariables;
    const Camera& camera = *data.camera;
    const std::vector<IGameObject*>& gameObjects = data.gameObjects;

    data.gameMap->draw(window, camera);

    for (size_t i=0; i<gameObjects.size(); ++i) {
        if (gameObjects[i]->isActive()) {
            gameObjects[i]->draw(window, camera);
        }
    }
}