#ifndef _GAME_H_
#define _GAME_H_

namespace sf {
    class RenderWindow;
}
class InputState;
class GameVariables;

class Game {
private:
    GameVariables* gameVariables = nullptr;

public:
    Game();
    ~Game();
    void initialise();
    void update(InputState& key);
    void draw(sf::RenderWindow& window);
};


#endif