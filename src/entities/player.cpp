#include "player.h"

Player::Player() {
	_type = EntityType::PLAYER;
	_lives = 3;
	_fuel = 100;
	setSize(Vector2(108, 44));
	setPosition(Vector2(50, 300));
	setSpeed(3);
}

void Player::update() {
	
}

void Player::onCollision(std::shared_ptr<Object> collisionPartner) {
	return;
	
	if(collisionPartner == nullptr) {
		_crashed = true;
		_lives -= 1;
		return;
	}
	
	auto entity = std::reinterpret_pointer_cast<Entity>(collisionPartner);

	auto entityType = entity->getType();



	if(entityType != EntityType::BASE && entityType != EntityType::FUEL && entityType != EntityType::MISSILE) {
		_crashed = true;
		_lives -= 1;
		return;
	}
}

void Player::moveUp() {
	if(getPosition().getY() + getSize().getY() >= WINDOW_HEIGHT) {
		return;
	}
	physics->move(this, 0, getSpeed());
}

void Player::moveDown() {
	if(getPosition().getY() <= 0) {
		return;
	}
	physics->move(this, 0, -getSpeed());
}

void Player::moveLeft() {
	if(getPosition().getX() <= 0) {
		return;
	}
	physics->move(this, -getSpeed(), 0);
}

void Player::moveRight() {
	if(getPosition().getX() + getSize().getX() >= WINDOW_WIDTH / 2) {
		return;
	}
	physics->move(this, getSpeed(), 0);
}

int Player::getLives() {
	return _lives;
}

void Player::setLives(int lives) {
	_lives = lives;
}

uint Player::getFuel() {
	return _fuel;
}

void Player::setFuel(uint fuel) {
	_fuel = fuel;
}