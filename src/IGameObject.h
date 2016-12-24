#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <cmath>

namespace sf {
    class RenderWindow;
}
class InputState;
class Camera;
class GameVariables;

class IGameObject {
public:
    bool isActive = true;
    float x, y;

    virtual void update(const InputState& key, GameVariables& data) = 0;
    virtual void draw(sf::RenderWindow& window, const Camera& camera) = 0;

    inline int gridX() {
        return std::round(x);
    }

    inline int gridY() {
        return std::round(y);
    }

    void destroy() {
        isActive = false;
    }
};


#endif