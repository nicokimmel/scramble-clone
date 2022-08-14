#ifndef SCRAMBLE_TEXTURE_H
#define SCRAMBLE_TEXTURE_H

#define FILE_HEADER_SIZE 14
#define INFORMATION_HEADER_SIZE 50

#include "../utils/base.h"
#include "../utils/bytes.h"

#include <fstream>
#include <vector>

/**
 * @brief Arten von Animationen
 */
enum AnimationType {
	STATIC, ONCE, REPEAT
};

/**
 * @brief Informationsblock über Sprites
 * @details Enthält den Animationstyp, die Anzahl der Bilder
 * 			innerhalb des Sprites und den Pfad zur Datei.
 */
struct SpriteInformation {
	AnimationType animationType;
	int spriteCount;
	std::string spriteFile;
};

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
		AnimationType _animationType = AnimationType::STATIC;
		bool _animationRunning = false;
		void generate(GLuint, char*);
		void buffer(const char*, uint, uint*, uint*);
	public:
		Texture(char*, uint, uint);
		Texture(const char*, uint);
		uint getWidth() const;
		uint getHeight() const;
		void setAnimationType(AnimationType);
		void toggleAnimation(bool);
		GLuint get();
		void next();
};

#endif //SCRAMBLE_TEXTURE_H