#ifndef SCRAMBLE_DRAWABLE_H
#define SCRAMBLE_DRAWABLE_H

#include "../utils/base.h"

/**
 * @brief Informationen über ein Objekt zum Zeichnen innerhalb der View
 * @details Wird von der View beim Zeichnen verwendet und ermöglicht es
 * 			Level- und Entityobjekte mit einer Funktion zu zeichnen.
 * 			Enthält einen Identifikator, die Breite, Höhe und Position des
 * 			Objektes.
 * 
 * @see View::render()
 */
struct RenderInformation {
	std::string identifier;
	int width;
	int height;
	int x;
	int y;
	uint rotation;
};

/**
 * @brief Interface der zu zeichnenden Objekte
 * 
 * @see Entity
 * @see Level
 */
class Drawable {
	public:
		virtual RenderInformation getRenderInformation() = 0;
};

#endif //SCRAMBLE_DRAWABLE_H