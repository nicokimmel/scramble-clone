#include "building.h"

/**
 * @brief Erstellt Objekt von Explosion
 * @details Setzt den Entitätentyp und
 * 			die Größe des Gebäudes.
 */
Building::Building() {
	_type = EntityType::BUILDING;
	setSize(Vector2(60, 69));
}

/**
 * @brief Update Funktion des Gebäudes
 * @details Wird bei jeder Iteration der Gameloop
 * 			aufgerufen.
 * 
 * @see Controller
 */
void Building::update() {
	
}

/**
 * @brief Kollisionsevent des Gebäudes
 * @details Setzt _crashed auf TRUE um dem Controller
 * 			mitzuteilen, dass es mit etwas kollidiert ist.
 * 
 * @see Controller
 * 
 * @param collisionPartner Kollisionspartner
 */
void Building::onCollision(EntityType entityType) {
	switch(entityType) {
		case EntityType::LASER:
		case EntityType::MISSILE: 
			_crashed = true;
	}
}