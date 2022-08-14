#include "rocket.h"

/**
 * @brief Erstellt Objekt von Rocket
 * @details Setzt den Entitätentyp und gibt der
 * 			Rakete die richtige Größe.
 */
Rocket::Rocket() {
	_type = EntityType::ROCKET;
	setSize(Vector2(28, 72));
}

/**
 * @brief Update Funktion der Rakete
 * @details Wird bei jeder Iteration der Gameloop
 * 			aufgerufen.
 * 
 * @see Controller
 */
void Rocket::update() {
	
}

/**
 * @brief Kollisionsevent der Rakete
 * @details Setzt _crashed auf TRUE um dem Controller
 * 			mitzuteilen, dass sie kollidiert ist.
 * 
 * @see Controller
 * 
 * @param collisionPartner Kollisionspartner
 */
void Rocket::onCollision(std::shared_ptr<Object> collisionPartner) {
	_crashed = true;
}

/**
 * @brief Lässt die Rakete nach oben steigen
 * @details Setzt die Y-Velocity auf 3 Pixel/Sekunde.
 * 
 */
void Rocket::launch() {
	setVelocity(Vector2(getVelocity().getX(), 3));
}