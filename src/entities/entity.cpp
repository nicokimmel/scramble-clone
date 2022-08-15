#include "entity.h"

Entity::Entity() {
	_type = EntityType::NONE;
	setPosition(Vector2(0, 0));
	setVelocity(Vector2(0, 0));
	setSpeed(0);
	setSize(0);
	setRotation(0);
	_crashed = false;
}

/**
 * @brief Updates Entity
 * @details Wird aus Controller aufgerufen und ruft die Update der jeweiligen Eintität auf und bewegt diese
 * 
 */
void Entity::updateEntity() {
	physics->move(this);
	update();
}

/**
 * @brief Gibt den Typ einer Entität zurück
 * @details Wird verwendet um zu überprüfen um welche Art von Entität es sich handelt
 * 
 * @return Entitäten Typ als Enum Konstante
 */
EntityType Entity::getType() {
	return _type;
}

/**
 * @brief Gibt den Typ einer Entität zurück
 * @details Wird verwendet um zu überprüfen um welche Art von Entität es sich handelt
 * 
 * @return Entitäten Typ als int id
 */
int Entity::getIdentifier() {
	return _type;
}

/**
 * @brief Gibt Koordinaten zurück
 * @details Wird verwendet um die Koordinaten einer Entität auszulesen
 * @return Vector2
 */
Vector2 Entity::getPosition() {
	return Object::getPosition();
}

/**
 * @brief Gibt Größe zurück
 * @details Wird verwendet um die Größe einer Entität auszulesen
 * @return Vector2
 */
Vector2 Entity::getSize() {
	return Object::getSize();
}

/**
 * @brief Gibt die Rotation zurück
 * @details Wird verwendet um die Rotation einer Entität auszulesen
 * @return int
 */
int Entity::getRotation() {
	return Object::getRotation();
}

/**
 * @brief Gibt einen boolean zurück ob eine Entität gecrashed ist
 * @details Wird verwendet um zu bestimmen ob nun eine Entität kollidiert ist oder nicht
 * @return boolean
 */
bool Entity::hasCrashed() {
	return _crashed;
}