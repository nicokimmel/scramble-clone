#include "entity.h"

Entity::Entity() {
	_type = EntityType::NONE;
	setPosition(Vector2(0, 0));
	setVelocity(Vector2(0, 0));
	setSpeed(0);
	setSize(0);
	setRotation(0);
	_crashed = false;
}

void Entity::updateEntity() {
	physics->move(this);
	update();
}

EntityType Entity::getType() {
	return _type;
}

bool Entity::hasCrashed() {
	return _crashed;
}

RenderInformation Entity::getRenderInformation() {
	RenderInformation info;
	info.identifier = EntityName[_type];
	info.width = getSize().getX();
	info.height = getSize().getY();
	info.x = getPosition().getX();
	info.y = getPosition().getY();
	info.rotation = getRotation();

	return info;
}