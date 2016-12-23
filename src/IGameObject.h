#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <cmath>

namespace sf {
    class RenderWindow;
}
class KeyboardState;

class IGameObject {
public:
    float x, y;

    virtual update(const KeyboardState& key) = 0;
    virtual draw(sf::RenderWindow& window) = 0;

    inline int gridX() {
        return std::round(x);
    }

    inline int gridY() {
        return std::round(y);
    }
};


#endif