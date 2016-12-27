#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

#include <cstddef>

typedef unsigned long long GameObjectID;
typedef size_t ObjectIndex;

extern const ObjectIndex INVALID_INDEX;
struct GameObjectRef {
    GameObjectID id;
    ObjectIndex index;

    GameObjectRef(): id(0) {}
    GameObjectRef(GameObjectID id): id(id) {}
    inline bool isValid() {return index != INVALID_INDEX;}
    inline void makeInvalid() {index = INVALID_INDEX;}
};

#endif