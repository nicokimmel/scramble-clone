#ifndef SCRAMBLE_DRAWABLE_H
#define SCRAMBLE_DRAWABLE_H

#include "../utils/base.h"

#include "../physics/vector2.h"

/**
 * @brief Interface der zu zeichnenden Objekte
 * 
 * @see Entity
 * @see Level
 */
class Drawable {
	public:
		virtual int getIdentifier() = 0;
		virtual Vector2 getSize() = 0;
		virtual Vector2 getPosition() = 0;
		virtual int getRotation() = 0;
};

#endif //SCRAMBLE_DRAWABLE_H