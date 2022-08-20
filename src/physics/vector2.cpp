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
int Vector2::getX() const {
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
int Vector2::getY() const {
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
	_x += vector.getX();
	_y += vector.getY();
	return *this;
}

/**
 * @brief Addiert gegebenen Vektor mit anderem Vektor
 * 
 * @param x Erster Wert des zweiten Vektors
 * @param y Zweiter Wert des zweiten Vektors
 * @return Neuer Vektor, der sich aus der Addition ergibt.  
 */
Vector2 Vector2::add(int x, int y) {
	_x += x;
	_y += y;
	return *this;
}

/**
 * @brief Multipliziert gegebenen Vektor mit anderem Vektor
 * 
 * @param vector Zweiter Vektor
 * @return Neuer Vektor, der sich aus der Multiplikation ergibt. 
 */
Vector2 Vector2::multiply(Vector2 vector) {
	_x *= vector.getX();
	_y *= vector.getY();
	return *this;
}

/**
 * @brief Überprüft Vektor auf Gleichheit
 * 
 * @param vector Zweiter Vektor
 * @return bool Gleichheit
 */
bool Vector2::operator==(const Vector2 vector) {
	if(_x == vector.getX()
		&& _y == vector.getY()) {
		return true;	
	}
	return false;
}

/**
 * @brief Überprüft Vektor auf Ungleichheit
 * 
 * @param vector Zweiter Vektor
 * @return bool Ungleichheit
 */
bool Vector2::operator!=(const Vector2 vector) {
	if(_x != vector.getX()
		|| _y != vector.getY()) {
		return true;	
	}
	return false;
}

/**
 * @brief Addiert Vektor mit anderem Vektor
 * 
 * @param vector Zweiter Vektor
 * @return Vector2 Vektor (Value)
 */
Vector2 Vector2::operator+(const Vector2 vector) {
	return Vector2(_x + vector.getX(), _y + vector.getY());
}

/**
 * @brief Addiert Vektor mit anderem Vektor
 * 
 * @param vector Zweiter Vektor
 * @return Vector2 Vektor (Reference)
 */
Vector2 Vector2::operator+=(const Vector2 vector) {
	_x += vector.getX();
	_y += vector.getY();
	return *this;
}

/**
 * @brief Subtrahiert Vektor mit anderem Vektor
 * 
 * @param vector Zweiter Vektor
 * @return Vector2 Vektor (Value)
 */
Vector2 Vector2::operator-(const Vector2 vector) {
	return Vector2(_x - vector.getX(), _y - vector.getY());
}

/**
 * @brief Subtrahiert Vektor mit anderem Vektor
 * 
 * @param vector Zweiter Vektor
 * @return Vector2 Vektor (Reference)
 */
Vector2 Vector2::operator-=(const Vector2 vector) {
	_x -= vector.getX();
	_y -= vector.getY();
	return *this;
}