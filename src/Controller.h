#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "InputState.h"

class Controller {
private:
    bool inGame;
    Game game;

    sf::RenderWindow window;
    InputState key;

    void processEvent(sf::Event event);
    void update();
    void draw();

public:
    Controller();
    void runMainLoop();
};


#endif