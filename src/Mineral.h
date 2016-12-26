#ifndef _MINERAL_H_
#define _MINERAL_H_

#include <SFML/Graphics.hpp>
#include "IGameObject.h"
class GameMap;

class Mineral : public IGameObject {
private:
    sf::RectangleShape shape;

public:
    const int gridX;
    const int gridY;

    Mineral(int gridX, int gridY, const GameMap& gameMap);
    virtual void update(const InputState& key, GameVariables& data);
    virtual void draw(sf::RenderWindow& window, const Camera& camera);

};

#endif