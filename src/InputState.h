#ifndef _INPUT_STATE_H_
#define _INPUT_STATE_H_

#include <SFML/Graphics.hpp>

class InputState {
public:
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    bool space_click = false;
    bool enter_click = false;

    bool leftmouse_click = false;
    bool rightmouse_click = false;

    inline void resetKeys() {
        space_click = false;
        enter_click = false;

        leftmouse_click = false;
        rightmouse_click = false;
    }

    inline void keyDown(sf::Keyboard::Key keyCode) {
        switch(keyCode) {
            case sf::Keyboard::Up: up = true; break;
            case sf::Keyboard::Down: down = true; break;
            case sf::Keyboard::Left: left = true; break;
            case sf::Keyboard::Right: right = true; break;

            case sf::Keyboard::Space: space_click = true; break;
            case sf::Keyboard::Return: enter_click = true; break;
        }
    }

    inline void keyUp(sf::Keyboard::Key keyCode) {
        switch(keyCode) {
            case sf::Keyboard::Up: up = false; break;
            case sf::Keyboard::Down: down = false; break;
            case sf::Keyboard::Left: left = false; break;
            case sf::Keyboard::Right: right = false; break;
        }
    }

    inline void mouseClick(sf::Mouse::Button button, int x, int y) {
        switch(button) {
            case sf::Mouse::Left: leftmouse_click = true;
            case sf::Mouse::Right: rightmouse_click = true;
        }
    }
};


#endif