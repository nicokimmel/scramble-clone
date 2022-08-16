#include "fuel.h"

/**
 * @brief Erstellt Objekt von Fuel
 * @details Setzt den Entitätentyp und die Größe
 */
Fuel::Fuel() {
	_type = EntityType::FUEL;
	setSize(Vector2(60, 69));
}

/**
 * @brief Update Funktion des Fuels
 * @details Wird bei jeder Iteration der Gameloop
 * 			aufgerufen.
 * 
 * @see Controller
 */
void Fuel::update() {
	
}

/**
 * @brief Kollisionsevent des Fuels
 * @details Setzt _crashed auf TRUE um dem Controller
 * 			mitzuteilen, dass er mit etwas kollidiert ist.
 * 
 * @see Controller
 * 
 * @param collisionPartner Kollisionspartner
 */
void Fuel::onCollision(EntityType entityType) {
	switch(entityType) {
		case EntityType::LASER:
		case EntityType::MISSILE:
			_crashed = true;
			break;
	}
}