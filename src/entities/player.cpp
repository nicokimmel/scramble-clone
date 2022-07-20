#include "player.h"

Player::Player() {
	_type = EntityType::PLAYER;
	_size = Vector2(108, 44);
	_position = Vector2(50, 300);
	_speed = 3;
	_lives = 3;
	_failed = false;
}

void Player::update() {
	
}

void Player::onCollision(std::shared_ptr<Entity> collisionPartner) {
	if(collisionPartner == nullptr) {
		_failed = true;
		_lives -= 1;
		return;
	}
	
	auto entityType = collisionPartner->getType();
	if(entityType != EntityType::BASE && entityType != EntityType::FUEL) {
		_failed = true;
		_lives -= 1;
		return;
	}
}

void Player::moveUp() {
	if(getPosition().getY() + getSize().getY() >= WINDOW_HEIGHT) {
		return;
	}
	Vector2 newPosition = getPosition().add(0, getSpeed());
	setPosition(newPosition);
}

void Player::moveDown() {
	if(getPosition().getY() <= 0) {
		return;
	}
	Vector2 newPosition = getPosition().add(0, -getSpeed());
	setPosition(newPosition);
}

void Player::moveLeft() {
	if(getPosition().getX() <= 0) {
		return;
	}
	Vector2 newPosition = getPosition().add(-getSpeed(), 0);
	setPosition(newPosition);
}

void Player::moveRight() {
	if(getPosition().getX() + getSize().getX() >= WINDOW_WIDTH / 2) {
		return;
	}
	Vector2 newPosition = getPosition().add(getSpeed(), 0);
	setPosition(newPosition);
}

int Player::getLives() {
	return _lives;
}

void Player::setLives(int lives) {
	_lives = lives;
}

bool Player::hasFailed() {
	return _failed;
}