#include "laser.h"

/**
 * @brief Erstellt Objekt von Laser
 * @details Setzt den Entitätentyp, die Größe
 * 			und die Velocity des Lasers.
 */
Laser::Laser() {
	_type = EntityType::LASER;
	setSize(Vector2(7, 10));
	setVelocity(Vector2(15, 0));
}

/**
 * @brief Update Funktion des Lasers
 * @details Wird bei jeder Iteration der Gameloop
 * 			aufgerufen.
 * 
 * @see Controller
 */
void Laser::update() {
	
}

/**
 * @brief Kollisionsevent des Lasers
 * @details Setzt _crashed auf TRUE um dem Controller
 * 			mitzuteilen, dass er mit etwas kollidiert ist.
 * 
 * @see Controller
 * 
 * @param collisionPartner Kollisionspartner
 */
void Laser::onCollision(EntityType entityType) {
	switch(entityType) {
		case EntityType::FUEL:
		case EntityType::NONE:
		case EntityType::ROCKET:
		case EntityType::BUILDING:
			_crashed = true;
			break;
	}
}