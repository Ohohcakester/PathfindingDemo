#include "RetrieverBot.h"
#include "Camera.h"
#include "GameVariables.h"
#include "GameMap.h"
#include "InputState.h"
#include "ExplorerBot.h"
#include "Mineral.h"

RetrieverBot::RetrieverBot(int x, int y, GameObjectRef explorerBotRef)
: explorerBotRef(explorerBotRef) {
    this->x = x;
    this->y = y;
    this->speed = 5;

    shape.setFillColor(sf::Color::Yellow);
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
}

void RetrieverBot::goPickUp(GameObjectRef mineralRef, const GameVariables& data) {
    Mineral* mineral = data.getGameObject<Mineral>(mineralRef);
    if (mineral == nullptr) return;
    
    goToPosition(mineral->x, mineral->y, *data.gameMap);
    state = RetrieverBotState::go_to_collect;

    targetMineralRef = mineralRef;
}

void RetrieverBot::update(const InputState& key, GameVariables& data) {
    if (state == RetrieverBotState::idle) return;

    // Verify destination
    GridVertex destination;
    switch(state) {
        case RetrieverBotState::go_to_collect: {
            Mineral* mineral = data.getGameObject<Mineral>(targetMineralRef);
            if (mineral != nullptr) {
                destination = GridVertex(mineral->gridX, mineral->gridY);
            } else {
                destroy();
                return;
            }
            break;
        }
        case RetrieverBotState::carrying_mineral: {
            IGameObject* bot = data.getGameObject(explorerBotRef);
            if (bot != nullptr) {
                int destX = bot->x, destY = bot->y;
                data.gameMap->getNearestGridCoordinate(destX, destY);
                destination = GridVertex(destX, destY);
            } else {
                destroy();
                return;
            }
            break;
        }
    }

    if (stoppedAndReachedDestination(destination, *data.gameMap)) {
        // OnReach
        switch(state) {
            case RetrieverBotState::go_to_collect: {
                onReachMineral(data);
                break;
            }
            case RetrieverBotState::carrying_mineral: {
                data.mineralManager.removeMineral(targetMineralRef.id, data);
                destroy();
                return;
            }
        }
    } else {
        // Haven't reached.
        switch(state) {
            case RetrieverBotState::carrying_mineral: {
                whileCarryingMineral(data);
            }
        }
    }
    followPath(*data.gameMap);
}

void RetrieverBot::onReachMineral(const GameVariables& data) {
    Mineral* mineral = data.getGameObject<Mineral>(targetMineralRef);
    if (mineral->isTaken()) {
        destroy();
        return;
    }

    mineral->pickUp(getId(), data);
    state = RetrieverBotState::carrying_mineral;
    returningStartFrame = data.frame%repath_interval;
    pathToExplorerBot(data);
}

void RetrieverBot::whileCarryingMineral(const GameVariables& data) {
    if (hasLineOfSightTo(explorerBotRef, data) || 
    data.frame%repath_interval == returningStartFrame) {
        pathToExplorerBot(data);
    }
}

bool RetrieverBot::hasLineOfSightTo(GameObjectRef& ref, const GameVariables& data) {
    int x1 = x, y1 = y;
    IGameObject* bot = data.getGameObject(ref);
    int x2 = bot->x, y2 = bot->y;

    const GameMap& gameMap = *data.gameMap;
    gameMap.getNearestGridCoordinate(x1, y1);
    gameMap.getNearestGridCoordinate(x2, y2);
    return gameMap.lineOfSight(x1, y1, x2, y2);
}

void RetrieverBot::pathToExplorerBot(const GameVariables& data) {
    IGameObject* bot = data.getGameObject(explorerBotRef);
    goToPosition(bot->x, bot->y, *data.gameMap);
}

void RetrieverBot::draw(sf::RenderWindow& window, const Camera& camera) {
    int drawX = x, drawY = y;
    camera.absToRel(drawX, drawY);
    shape.setPosition(drawX, drawY);
    window.draw(shape);
}

