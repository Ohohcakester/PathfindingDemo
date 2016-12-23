#ifndef _EXPLORER_BOT_H_
#define _EXPLORER_BOT_H_

#include "PathFollower.h"

class ExplorerBot: public PathFollower {
public:
    ExplorerBot(int x, int y);
    virtual void update(const KeyboardState& key);
    virtual void draw(sf::RenderWindow& window, const Camera& camera);
};

#endif