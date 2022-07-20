#include "vector2.h"

/**
 * @brief Erstellt zweidimensionalen Vektor
 * 
 * @param x Erster Wert
 * @param y Zweiter Wert
 */
Vector2::Vector2(int x, int y) {
	_x = x;
	_y = y;
}

/**
 * @brief Gibt den X Wert zurück
 * 
 * @return X Wert
 */
int Vector2::getX() {
	return _x;
}

/**
 * @brief Setzt den X Wert
 * 
 * @param x X Wert
 */
void Vector2::setX(int x) {
	_x = x;
}

/**
 * @brief Gibt den Y Wert zurück
 * 
 * @return Y Wert
 */
int Vector2::getY() {
	return _y;
}

/**
 * @brief Setzt den Y Wert
 * 
 * @param y Y Wert
 */
void Vector2::setY(int y) {
	_y = y;
}

/**
 * @brief Addiert gegebenen Vektor mit anderem Vektor
 * 
 * @param vector Zweiter Vektor
 * @return Neuer Vektor, der sich aus der Addition ergibt. 
 */
Vector2 Vector2::add(Vector2 vector) {
	int newX = _x + vector.getX();
	int newY = _y + vector.getY();
	return Vector2(newX, newY);
}

/**
 * @brief Addiert gegebenen Vektor mit anderem Vektor
 * 
 * @param x Erster Wert des zweiten Vektors
 * @param y Zweiter Wert des zweiten Vektors
 * @return Neuer Vektor, der sich aus der Addition ergibt.  
 */
Vector2 Vector2::add(int x, int y) {
	int newX = _x + x;
	int newY = _y + y;
	return Vector2(newX, newY);
}

/**
 * @brief Multipliziert gegebenen Vektor mit anderem Vektor
 * 
 * @param vector Zweiter Vektor
 * @return Neuer Vektor, der sich aus der Multiplikation ergibt. 
 */
Vector2 Vector2::multiply(Vector2 vector) {
	int x = _x * vector.getX();
	int y = _y * vector.getY();
	return Vector2(x, y);
}