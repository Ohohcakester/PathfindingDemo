#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "DataTypes.h"
#include <cmath>
#include <iostream>

namespace sf {
    class RenderWindow;
}
class InputState;
class Camera;
class GameVariables;

class IGameObject {
private:
    bool idAlreadySet = false;
    GameObjectID id;
    bool active = true;

public:
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
        active = false;
    }

    inline bool isActive() {return active;}

    inline GameObjectID getId() {return id;}

    inline void setId(GameObjectID _id) {
        if (idAlreadySet) std::cout << "ERROR: ID Already set!" << std::endl;
        idAlreadySet = true;
        this->id = _id;
    }
};


#endif