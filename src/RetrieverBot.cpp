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
    IGameObject* gameObject = data.getGameObject(targetMineralRef);
    if (gameObject == nullptr) return;
    Mineral* mineral = static_cast<Mineral*>(gameObject);
    
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
            if (data.gameObjectExists(targetMineralRef)) {
                Mineral* mineral = static_cast<Mineral*>(data.getGameObject(targetMineralRef));
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

    const int repath_interval = 30;

    if (stoppedAndReachedDestination(destination, *data.gameMap)) {
        // OnReach
        switch(state) {
            case RetrieverBotState::go_to_collect: {
                state = RetrieverBotState::carrying_mineral;
                returningStartFrame = data.frame%repath_interval;
                pathToExplorerBot(data);
                break;
            }
            case RetrieverBotState::carrying_mineral: {
                data.mineralManager.removeMineral(targetMineralRef.id);
                destroy();
                return;
            }
        }
    } else {
        // Haven't reached.
        if (data.frame%repath_interval == returningStartFrame) {
            pathToExplorerBot(data);
        }
    }
    followPath(*data.gameMap);
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

