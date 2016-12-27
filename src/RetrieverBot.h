#ifndef _RETRIEVER_BOT_H_
#define _RETRIEVER_BOT_H_

#include <SFML/Graphics.hpp>
#include "PathFollower.h"
#include "DataTypes.h"
class GameMap;
class Camera;
class GameVariables;
class InputState;

namespace RetrieverBotState {
    enum Enum {
        idle,
        go_to_collect,
        carrying_mineral
    };
}

class RetrieverBot: public PathFollower {
public:
    RetrieverBot(int x, int y);
    void goPickUp(GameObjectRef mineralRef, const GameVariables& data);
    virtual void update(const InputState& key, GameVariables& data);
    virtual void draw(sf::RenderWindow& window, const Camera& camera);

private:
    int radius = 5;
    sf::CircleShape shape;
    RetrieverBotState::Enum state = RetrieverBotState::idle;
    GameObjectRef targetMineralRef;
    GameObjectRef explorerBotRef;
    int returningStartFrame;

    void pathToExplorerBot(const GameVariables& gameVariables);
};

#endif