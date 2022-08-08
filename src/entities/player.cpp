#include "player.h"

Player::Player() {
	_type = EntityType::PLAYER;
	_size = Vector2(108, 44);
	_position = Vector2(50, 300);
	_speed = 3;
	_lives = 3;
	_fuel = 100;
}

void Player::update() {
	
}

void Player::onCollision(std::shared_ptr<Entity> collisionPartner) {
	return;
	
	if(collisionPartner == nullptr) {
		_crashed = true;
		_lives -= 1;
		return;
	}
	
	auto entityType = collisionPartner->getType();
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