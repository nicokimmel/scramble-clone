#include "Object.h"

void Object::setMax(Vector2 max) {
    _max = max;
}

void Object::setMin(Vector2 min) {
    _min = min;
}

Vector2 Object::getMax() {
    return _max;
}

Vector2 Object::getMin() {
    return _min;
}

