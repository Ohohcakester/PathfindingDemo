#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <cmath>

namespace sf {
    class RenderWindow;
}
class KeyboardState;
class Camera;

class IGameObject {
public:
    float x, y;

    virtual void update(const KeyboardState& key) = 0;
    virtual void draw(sf::RenderWindow& window, const Camera& camera) = 0;

    inline int gridX() {
        return std::round(x);
    }

    inline int gridY() {
        return std::round(y);
    }
};


#endif