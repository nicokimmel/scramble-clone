#include "Object.h"
/*
void Object::setVelocity(Vector2 v) {
    _v = v;
}

void Object::setPosition(Vector2 pos) {
    _pos = pos;
}
*/
void Object::setMax(Vector2 max) {
    _max = max;
}

void Object::setMin(Vector2 min) {
    _min = min;
}
/*
void Object::setRotation(float rotation) {
    _rotation = rotation;
}

Vector2 Object::getVelocity() {
    return _v;
}

Vector2 Object::getPosition() {
    return _pos;
}

float Object::getRotation() {
    return _rotation;
}
*/
Vector2 Object::getMax() {
    return _max;
}

Vector2 Object::getMin() {
    return _min;
}

