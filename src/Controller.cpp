#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "GameGlobals.h"

Controller::Controller(): inGame(true), window(sf::VideoMode(RES_X, RES_Y), "Pathfinding Demo") {
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
    }
}

void Controller::update() {
    game.update(key);
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

        while (dTime > frameTime) {
            dTime -= frameTime;
            update();
        }

        window.clear();
        draw();
    }
}