#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Gameglobals.h"
class InputState;

class Camera {
public:
    int x;
    int y;
    int slowSpeed = 5;
    int fastSpeed = 15;

    Camera();
    void update(InputState& key);

    inline void absToRel(int& cx, int& cy) const {
        cx = cx - x + RES_X/2;
        cy = y - cy + RES_Y/2;
    }

    inline void relToAbs(int& cx, int& cy) const {
        cx = cx + x - RES_X/2;
        cy = y - cy + RES_Y/2;
    }
};


#endif
