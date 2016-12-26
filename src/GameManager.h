#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

class GameVariables;
class InputState;

class GameManager {
public:
    GameManager() {}
    void initialise(GameVariables& data) const;
    void update(const InputState& key, GameVariables& data) const;
};

#endif