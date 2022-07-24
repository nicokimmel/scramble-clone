#include "entity.h"

Entity::Entity() {
	_type = EntityType::NONE;
	_position = Vector2(0, 0);
	_velocity = Vector2(0, 0);
	_speed = 0;
	_size = 0;
}

void Entity::updateEntity() {
	if(this->getType() != ROCKET) {
		//physics->move(*this);
	} else {
		if (getPosition().getX() < 400) {
			//physics->move(*this);
		}
	}

	//physics->move(*this);
	//this->setPosition(Vector2(this->getPosition().getX() + this->getVelocity().getX(), this->getPosition().getY() + this->getVelocity().getY()));
	//(&(*this))->setPosition(Vector2(this->getPosition().getX() + this->getVelocity().getX(), this->getPosition().getY() + this->getVelocity().getY()));
	
	//setPosition(getPosition().add(getVelocity()));
	update();
}

EntityType Entity::getType() {
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

RenderInformation Entity::getRenderInformation() {
	RenderInformation info;
	info.identifier = EntityName[_type];
	info.width = _size.getX();
	info.height = _size.getY();
	info.x = _position.getX();
	info.y = _position.getY();
	return info;
}