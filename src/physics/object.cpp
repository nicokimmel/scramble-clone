#include "object.h"

Object::Object() {
    
}

Vector2 Object::getPosition() {
	return _position;
}

void Object::setPosition(Vector2 position) {
	_position = position;
}

Vector2 Object::getVelocity() {
	return _velocity;
}

void Object::setVelocity(Vector2 velocity) {
	_velocity = velocity;
}

uint Object::getSpeed() {
	return _speed;
}

void Object::setSpeed(uint speed) {
	_speed = speed;
}

Vector2 Object::getSize() {
	return _size;
}

void Object::setSize(Vector2 size) {
	_size = size;
}

int Object::getRotation() {
	return _rotation;
}

void Object::setRotation(int rotation) {
	_rotation = rotation;
}

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

