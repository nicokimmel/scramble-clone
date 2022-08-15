#include "object.h"

/**
 * @brief Gibt Koordinaten zurück
 * @details Wird verwendet um die Koordinaten eines Objekts auszulesen
 * 
 * @return Vector2
 */
Vector2 Object::getPosition() {
	return _position;
}

/**
 * @brief Setzt Position neu
 * @details Verwendbar um die aktuelle Position eines Objektes zu überschreiben
 * 
 * @param position Vector2
 */
void Object::setPosition(Vector2 position) {
	_position = position;
}

/**
 * @brief Gibt Geschwindigkeit als Vektor zurück 
 * @details Wird verwendet um die aktuelle Geschwindigkeit eines Objekts auszulesen
 * 
 * @return Vector2
 */
Vector2 Object::getVelocity() {
	return _velocity;
}

/**
 * @brief Setzt Geschwindigkeit neu
 * @details Verwendbar um die aktuelle Geschwindigkeit eines Objektes zu überschreiben
 * 
 * @param velocity Vector2
 */
void Object::setVelocity(Vector2 velocity) {
	_velocity = velocity;
}

/**
 * @brief Gibt zurückgelegte Strecke über Zeit als Skalar zurück
 * @details Wird verwendet um für den Player das Bewegen zu ermöglichen
 * 
 * @return int
 */
uint Object::getSpeed() {
	return _speed;
}

/**
 * @brief Setzt Skaler zurückgelegte Strecke über Zeit neu
 * @details Verwendbar um den aktuelle Skaler zurückgelegte Strecke über Zeit eines Objektes neu zu setzen
 * 
 * @param speed int
 */
void Object::setSpeed(uint speed) {
	_speed = speed;
}

/**
 * @brief Gibt Größe zurück
 * @details Wird verwendet um die Größe einer Entität auszulesen
 * 
 * @return Vector2
 */
Vector2 Object::getSize() {
	return _size;
}

/**
 * @brief Setzt Ausdehnung eines Objektes
 * @details Kann verwendet werden um die Ausdehnung eines Objektes in die x und y Richtung neu zu setzen
 * 
 * @param size Vector2
 */
void Object::setSize(Vector2 size) {
	_size = size;
}

/**
 * @brief Gibt die Rotation zurück
 * @details Wird verwendet um die Rotation einer Entität auszulesen
 * 
 * @return int
 */
int Object::getRotation() {
	return _rotation;
}

/**
 * @brief Setzt Rotation eines Objektes
 * @details Wird verwendet um die aktuelle Rotation eines Objekts zu überschreiben
 * 
 * @param rotation int
 */
void Object::setRotation(int rotation) {
	_rotation = rotation;
}