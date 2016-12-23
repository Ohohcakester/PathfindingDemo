#ifndef _GAME_H_
#define _GAME_H_

namespace sf {
    class RenderWindow;
}
class KeyboardState;
class GameVariables;

class Game {
private:
    GameVariables* gameVariables = nullptr;

public:
    Game();
    ~Game();
    void initialise();
    void update(KeyboardState& key);
    void draw(sf::RenderWindow& window);
};


#endif