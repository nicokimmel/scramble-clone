#include "entity.h"

//TODO: Dokumentieren
Entity::Entity() {
	_type = EntityType::NONE;
	_crashed = false;
	setPosition(Vector2(0, 0));
	setVelocity(Vector2(0, 0));
	setSpeed(0);
	setSize(0);
	setRotation(0);
}

//TODO: Marlon fragen wieso Physics Pointer funktioniert ohne Initialisierung
void Entity::updateEntity() {
	_physics->move(this);
	update();
}

EntityType Entity::getType() {
	return _type;
}

int Entity::getIdentifier() {
	return _type;
}

Vector2 Entity::getPosition() {
	return _position;
}

void Entity::setPosition(Vector2 position) {
	_position = position;
}

Vector2 Entity::getVelocity() {
	return _velocity;
}

void Entity::setVelocity(Vector2 velocity) {
	_velocity = velocity;
}

uint Entity::getSpeed() {
	return _speed;
}

void Entity::setSpeed(uint speed) {
	_speed = speed;
}

Vector2 Entity::getSize() {
	return _size;
}

void Entity::setSize(Vector2 size) {
	_size = size;
}

int Entity::getRotation() {
	return _rotation;
}

void Entity::setRotation(int rotation) {
	_rotation = rotation;
}

bool Entity::hasCrashed() {
	return _crashed;
}