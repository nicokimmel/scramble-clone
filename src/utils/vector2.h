#ifndef SCRAMBLE_VECTOR2_H
#define SCRAMBLE_VECTOR2_H

/**
 * @brief Bildet zweidimensionalen Vektor (Tupel) ab
 */
class Vector2 {
	private:
		int _x;
		int _y;
	public:
		Vector2(int = 0, int = 0);
		int getX();
		void setX(int);
		int getY();
		void setY(int);
		Vector2 add(Vector2);
		Vector2 add(int, int);
		Vector2 multiply(Vector2);
};

#endif //SCRAMBLE_VECTOR2_H