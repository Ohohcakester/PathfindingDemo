#ifndef _GAME_H_
#define _GAME_H_

#include "GameVariables.h"
#include "GameManager.h"
namespace sf {
    class RenderWindow;
}
class InputState;


class Game {
private:
    std::unique_ptr<GameVariables> gameVariables;
    const GameManager gameManager;

public:
    Game();
    void initialise();
    void update(InputState& key);
    void draw(sf::RenderWindow& window);
};


#endif