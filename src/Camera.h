#ifndef _CAMERA_H_
#define _CAMERA_H_

class InputState;

class Camera {
public:
    int x;
    int y;
    int slowSpeed = 5;
    int fastSpeed = 15;

    Camera();
    void update(InputState& key);
    void absToRel(int& cx, int& cy) const;
    void relToAbs(int& cx, int& cy) const;
};


#endif
