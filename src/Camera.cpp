#include "Camera.h"
#include "InputState.h"
#include <iostream>

Camera::Camera(): x(0), y(0) {

}

void Camera::update(InputState& key) {
    int vx = 0;
    int vy = 0;

    int speed = key.z || key.space ? fastSpeed : slowSpeed;
    if (key.up || key.w) vy += speed;
    if (key.down || key.s) vy -= speed;
    if (key.left || key.a) vx -= speed;
    if (key.right || key.d) vx += speed;

    x += vx;
    y += vy;
}















