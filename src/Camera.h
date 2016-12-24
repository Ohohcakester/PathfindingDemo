#ifndef _CAMERA_H_
#define _CAMERA_H_

class InputState;

class Camera {
public:
    int x;
    int y;
    int speed = 5;

    Camera();
    void update(InputState& key);
    void absToRel(int& cx, int& cy) const;
    void relToAbs(int& cx, int& cy) const;
};


#endif
