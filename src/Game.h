#ifndef _GAME_H_
#define _GAME_H_

#include "GameVariables.h"

namespace sf {
    class RenderWindow;
}
class KeyboardState;

class Game {
private:
    GameVariables data;

public:
    Game();
    void initialise();
    void update(KeyboardState& key);
    void draw(sf::RenderWindow& window);
};


#endif