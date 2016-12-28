#ifndef _EXPLORER_BOT_H_
#define _EXPLORER_BOT_H_

#include <SFML/Graphics.hpp>
#include "PathFollower.h"
#include "MarkedMinerals.h"
class GameMap;
class Camera;
class GameVariables;
class InputState;

class ExplorerBot: public PathFollower {
public:
    ExplorerBot(int x, int y);
    virtual void update(const InputState& key, GameVariables& data);
    virtual void draw(sf::RenderWindow& window, const Camera& camera);

private:
    int radius = 15;
    sf::CircleShape shape;
    MarkedMinerals markedMinerals;

    void retrieveRandomMineral(GameVariables& data);
};

#endif