#ifndef SCRAMBLE_TEXTURE_H
#define SCRAMBLE_TEXTURE_H

#define FILE_HEADER_SIZE 14
#define INFORMATION_HEADER_SIZE 50

#include "../utils/base.h"
#include "../utils/bytes.h"

#include <fstream>
#include <vector>

/**
 * @brief Hält Informationen über eine Textur
 * @details Bietet Funktionen um Bitmaps intern zu verwalten und
 * 			Informationen wie Höhe, Breite und Pixeldaten aus jener
 * 			auszulesen. Erstellt eine TextureID für OpenGL.
 * 
 * @todo Animationen
 */
class Texture {
	private:
		uint _width;
		uint _height;
		std::vector<GLuint> _spriteList;
		uint _currentSprite = 0;
		void generate(GLuint, char*);
		void buffer(const char*, uint, uint*, uint*);
	public:
		Texture(char*, uint, uint);
		Texture(const char*, uint);
		uint getWidth() const;
		uint getHeight() const;
		GLuint next();
};

#endif //SCRAMBLE_TEXTURE_H