#ifndef _CAMERA_H_
#define _CAMERA_H_

class KeyboardState;

class Camera {
public:
    int x;
    int y;
    int speed = 5;

    Camera();
    void update(KeyboardState& key);
};


#endif
