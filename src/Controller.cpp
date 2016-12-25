#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "GameGlobals.h"

Controller::Controller(): inGame(true), window(sf::VideoMode(RES_X, RES_Y), "Pathfinding Demo") {
    game.initialise();
}

void Controller::processEvent(sf::Event event) {
    switch(event.type) {
        case sf::Event::Closed: {
            window.close();
            break;
        }
        case sf::Event::KeyPressed: {
            key.keyDown(event.key.code);
            break;
        }
        case sf::Event::KeyReleased: {
            key.keyUp(event.key.code);
            break;
        }
        case sf::Event::MouseButtonPressed: {
            key.mouseClick(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
            break;
        }
    }
}

void Controller::update() {
    game.update(key);
    key.resetKeys();
}

void Controller::draw() {
    game.draw(window);
};

void Controller::runMainLoop() {
    sf::Clock clock;
    float frameTime = 1/60.0f;
    float dTime = 0;

    while (window.isOpen()) {
        dTime += clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            processEvent(event);
        }

        if (dTime > 5*frameTime) dTime = 5*frameTime;

        bool updated = false;
        while (dTime > frameTime) {
            dTime -= frameTime;
            update();
            updated = true;
        }

        if (updated) {
            window.clear();
            draw();
            window.display();
        }
    }
}