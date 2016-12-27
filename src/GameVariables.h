#ifndef _GAME_VARIABLES_H_
#define _GAME_VARIABLES_H_

#include "DataTypes.h"
#include "GameGlobals.h"
#include "GameMap.h"
#include "Camera.h"
#include "IGameObject.h"
#include "MineralManager.h"
#include <memory>
#include <vector>
#include <unordered_map>
class GameMap;
class Camera;
class IGameObject;

class GameVariables {
private:
    std::unordered_map<GameObjectID, ObjectIndex> idMap;
    GameObjectID nextAvailableID = 1;

public:
    std::unique_ptr<GameMap> gameMap;
    std::unique_ptr<Camera> camera;
    std::vector<IGameObject*> gameObjects;

    unsigned long long frame = 0;
    MineralManager mineralManager;

    GameVariables();
    ~GameVariables();

    inline void reallocateGameObjectsArray(size_t estimatedSize) {
        std::vector<IGameObject*> newGameObjects;
        // reserve, not resize. We have no guarantee that nActive remains the same after the update.
        newGameObjects.reserve(estimatedSize);

        for (size_t i=0; i<gameObjects.size(); ++i) {
            if (gameObjects[i]->isActive()) {
                newGameObjects.push_back(gameObjects[i]);
            } else {
                delete gameObjects[i];
            }
        }
        gameObjects.swap(newGameObjects);

        idMap.clear();
        idMap.reserve(gameObjects.size());
        for (size_t i=0; i<gameObjects.size(); ++i) {
            // all gameobjects are guaranteed to be active now.
            idMap[gameObjects[i]->getId()] = i;
        }
    }

    inline GameObjectID createObject(IGameObject* gameObject) {
        ObjectIndex index = gameObjects.size();
        GameObjectID id = nextAvailableID++;

        gameObject->setId(id);
        gameObjects.push_back(gameObject);
        idMap[id] = index;

        return id;
    }

    inline GameObjectRef getObjectReference(GameObjectID id) const {
        GameObjectRef ref(id);
        updateObjectReference(ref);
    }

    inline void updateObjectReference(GameObjectRef& ref) const {
        ref.index = INVALID_INDEX;

        const auto it = idMap.find(ref.id);
        if (it != idMap.end()) {
            ObjectIndex index = it->second;
            // it is guaranteed that index < gameOBjects.size()
            if (gameObjects[index]->isActive()) {
                ref.index = index;
            } // else object is already destroyed.
        }
    }

    inline IGameObject* getGameObject(GameObjectRef& ref) const {
        updateObjectReference(ref);
        return ref.index != INVALID_INDEX ? gameObjects[ref.index] : nullptr;
    }

    inline bool gameObjectExists(GameObjectRef& ref) const {
        updateObjectReference(ref);
        return ref.index != INVALID_INDEX;
    }
};

#endif