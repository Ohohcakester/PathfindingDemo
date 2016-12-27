#ifndef _MINERAL_H_
#define _MINERAL_H_

#include "DataTypes.h"
#include <SFML/Graphics.hpp>
#include "IGameObject.h"
class GameMap;

namespace MineralState {
    enum Enum {
        on_ground,
        carried
    };
}

class Mineral : public IGameObject {
private:
    sf::RectangleShape shape;
    MineralState::Enum state = MineralState::on_ground;
    GameObjectRef carrierRef;
    int lastCarrierX;
    int lastCarrierY;

public:
    int gridX;
    int gridY;

    Mineral(int gridX, int gridY, const GameMap& gameMap);
    virtual void update(const InputState& key, GameVariables& data);
    virtual void draw(sf::RenderWindow& window, const Camera& camera);

    void pickUp(GameObjectID retrieverBot, const GameVariables& data);
    void drop(int _gridX, int _gridY, const GameVariables& data);
    inline bool isTaken() {return state != MineralState::on_ground;}

private:
    void updateCarrierLocation(const GameVariables& data);
};

#endif