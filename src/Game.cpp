#include <SFML/Graphics.hpp>
#include "Game.h"
#include "KeyboardState.h"
#include "GameVariables.h"
#include "Camera.h"

Game::Game() {

}

Game::~Game() {
    if (data != nullptr) delete data;
}

void Game::initialise() {
    if (data != nullptr) {
        delete data;
        data = nullptr;
    }
    data = new GameVariables();
}

void Game::update(KeyboardState& key) {
    if (data == nullptr) return;

    data->camera->update(key);
}

void Game::draw(sf::RenderWindow& window) {

}