#include "player.h"

/**
 * @brief Erstellt Objekt von Player
 * @details Setzt den Entitätentyp, die Leben des Spieler,
 * 			den Tank, die Größe, Position und die Geschwindigkeit.
 */
Player::Player() {
	_type = EntityType::PLAYER;
	_lives = 3;
	_fuel = 100;
	setSize(Vector2(108, 44));
	setPosition(Vector2(50, 300));
	setSpeed(3);
}

/**
 * @brief Update Funktion des Spielers
 * @details Wird bei jeder Iteration der Gameloop
 * 			aufgerufen.
 * 
 * @see Controller
 */
void Player::update() {
	
}

/**
 * @brief Kollisionsevent des Spielers
 * @details Setzt bei einer Kollision _crashed auf TRUE
 * 			und zieht dem Spieler ein Leben ab.
 * 			Eine Kollisionspartner mit einem Zeiger auf den
 * 			nullptr schließt auf eine Kollision mit der Spielwelt.
 * 
 * @see Controller
 * 
 * @param collisionPartner Kollisionspartner
 */
void Player::onCollision(EntityType entityType) {
	switch(entityType) {
		case EntityType::FUEL:
		case EntityType::NONE:
		case EntityType::ROCKET:
		case EntityType::BUILDING:
			_crashed = true;
			_lives -= 1;
			break;
	}
}

/**
 * @brief Treibstoffevent des Spielers
 * @details Zieht jede halbe Sekunde 1 Tankeinheit ab.
 * 			Wenn der Tank auf 0 fällt wird die Geschwindigkeit
 * 			des Spielers auf 0 gesetzt, damit er sich nicht weiter
 * 			bewegen kann. Velocity wird auf einen festen Wert
 * 			gesetzt, der den Spieler zwangsweiße abstürzen lässt.
 */
void Player::onFuel() {
	if(_fuel == 0) {
        setSpeed(0);
        setVelocity(Vector2(2, -2));
    }
	_fuel--;
	std::cout << "FUEL: " << _fuel << "%" << std::endl;
}

/**
 * @brief Bewegt Spieler nach oben
 * @details Dabei wird die Fensterhöhe beachtet.
 * 
 * @see Physics
 */
void Player::moveUp() {
	if(getPosition().getY() + getSize().getY() >= WINDOW_HEIGHT - 2) {
		return;
	}
	_physics->move(shared_from_this(), 0, getSpeed());
}

/**
 * @brief Bewegt Spieler nach unten
 * @details Dabei wird die Fensterhöhe beachtet.
 * 
 * @see Physics
 */
void Player::moveDown() {
	if(getPosition().getY() <= 0) {
		return;
	}
	_physics->move(shared_from_this(), 0, -getSpeed());
}

/**
 * @brief Bewegt Spieler nach links
 * @details Dabei wird die Fensterbreite beachtet.
 * 
 * @see Physics
 */
void Player::moveLeft() {
	if(getPosition().getX() <= 0) {
		return;
	}
	_physics->move(shared_from_this(), -getSpeed(), 0);
}

/**
 * @brief Bewegt Spieler nach rechts
 * @details Dabei wird die Fensterbreite beachtet.
 * 
 * @see Physics
 */
void Player::moveRight() {
	if(getPosition().getX() + getSize().getX() >= WINDOW_WIDTH / 2) {
		return;
	}
	_physics->move(shared_from_this(), getSpeed(), 0);
}

/**
 * @brief Gibt Anzahl der Leben zurück
 * 
 * @return int Anzahl der Leben
 */
int Player::getLives() {
	return _lives;
}

/**
 * @brief Setzt Leben des Spielers
 * 
 * @param lives Anzahl der Leben
 */
void Player::setLives(int lives) {
	_lives = lives;
}

/**
 * @brief Gibt Treibstoffmenge des Spielers zurück
 * @details Treibstoffmenge liegt zwischen 0-100
 * 
 * @return uint Treibstoffmenge
 */
uint Player::getFuel() {
	return _fuel;
}

/**
 * @brief Setzt Treibstoffmenge des Spielers
 * @details Treibstoffmenge liegt zwischen 0-100
 * 
 * @param fuel Treibstoffmenge
 */
void Player::setFuel(uint fuel) {
	_fuel = std::min(fuel, (uint)100);;
}

/**
 * @brief Fügt dem Spieler Treibstoff hinzu
 * @details Treibstoffmenge liegt zwischen 0-100
 * 
 * @param fuel Treibstoffmenge
 */
void Player::addFuel(uint fuel) {
	_fuel = std::min(_fuel + fuel, (uint)100);
}