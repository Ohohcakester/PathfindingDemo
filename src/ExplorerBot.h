#ifndef _EXPLORER_BOT_H_
#define _EXPLORER_BOT_H_

#include "PathFollower.h"

class ExplorerBot: public PathFollower {
public:
    ExplorerBot(int x, int y);
    virtual void update(const InputState& key, GameVariables& data);
    virtual void draw(sf::RenderWindow& window, const Camera& camera) const;
};

#endif