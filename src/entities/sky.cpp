#include "sky.h"

/**
 * @brief Erstellt Objekt von Sky
 * @details Setzt den Entitätentyp und
 * 			die richtige Größe.
 */
Sky::Sky() {
	_type = EntityType::SKY;
	setSize(Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));
}

/**
 * @brief Update Funktion des Himmels
 * @details Wird bei jeder Iteration der Gameloop
 * 			aufgerufen.
 * 
 * @see Controller
 */
void Sky::update() {
	
}

/**
 * @brief Kollisionsevent des Himmels
 * @details Der Himmel hat keine Kollisionen
 * 
 * @see Controller
 * 
 * @param collisionPartner Kollisionspartner
 */
void Sky::onCollision(EntityType entityType) {
	
}