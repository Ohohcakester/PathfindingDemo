#include "Camera.h"
#include "InputState.h"
#include <iostream>

Camera::Camera(): x(0), y(0) {

}

void Camera::update(InputState& key) {
    int vx = 0;
    int vy = 0;

    int speed = key.z ? fastSpeed : slowSpeed;
    if (key.up) vy += speed;
    if (key.down) vy -= speed;
    if (key.left) vx -= speed;
    if (key.right) vx += speed;

    x += vx;
    y += vy;
}

void Camera::absToRel(int& cx, int& cy) const {
    cx = cx - x;
    cy = y - cy;
}

void Camera::relToAbs(int& cx, int& cy) const {
    cx = cx + x;
    cy = y - cy;
}

















