#include "missile.h"

/**
 * @brief Erstellt Objekt von Missile
 * @details Setzt den Entitätentyp und die Größe.
 * 			Initialisiert auch die Ticks, die für die
 * 			Bewegung der Missile genutzt werden.
 */
Missile::Missile() {
	_type = EntityType::MISSILE;
	_ticks = 1;
	setSize(Vector2(45, 22));
}

/**
 * @brief Update Funktion der Missile
 * @details Wird bei jeder Iteration der Gameloop
 * 			aufgerufen.
 * 			Bewegt die Rakete anhand von 3 Funktionen um
 * 			eine ähnliche Flugkurve wie beim Original zu
 * 			erhalten.
 * 			In die Funktion wird _ticks eingesetzt, was
 * 			der Zeit der Missile seit dem Spawn entspricht.
 * 
 * @see Controller
 * @see Rotation: https://media.discordapp.net/attachments/571475149472399360/1000024345348944053/unknown.png
 * @see X-Velocity: https://media.discordapp.net/attachments/571475149472399360/1000024493751816292/unknown.png
 * @see Y-Velocity: https://media.discordapp.net/attachments/571475149472399360/1000025243064225852/unknown.png
 */
void Missile::update() {
	_ticks += 1;
	
	setRotation(std::min(_ticks > 20 ? 120 * ((_ticks - 20.0f) / (_ticks - 1.0f)) : 0.0f, 90.0f));
	
	float xVel = std::max(-1 * std::pow(0.1f * _ticks - 2.0f, 2.0f) + 5, 0.0f);
	float yVel = std::min(_ticks > 30 ? std::pow(0.1f * _ticks - 2.0f, 2.0f) : 0, 5.0f) * -1;
	setVelocity(Vector2(xVel, yVel));
}

/**
 * @brief Kollisionsevent der Missile
 * @details Setzt _crashed auf TRUE um dem Controller
 * 			mitzuteilen, dass sie kollidiert ist.
 * 
 * @see Controller
 * 
 * @param collisionPartner Kollisionspartner
 */
void Missile::onCollision(std::shared_ptr<Object> collisionPartner) {
	_crashed = true;
}