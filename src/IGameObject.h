#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <cmath>

namespace sf {
    class RenderWindow;
}
class KeyboardState;
class Camera;
class GameVariables;

class IGameObject {
public:
    float x, y;

    virtual void update(const KeyboardState& key, GameVariables& data) = 0;
    virtual void draw(sf::RenderWindow& window, const Camera& camera) const = 0;

    inline int gridX() {
        return std::round(x);
    }

    inline int gridY() {
        return std::round(y);
    }
};


#endif