#include "texture.h"

/**
 * @brief Erstellt Objekt der Texturenklasse
 * @details Dieser Konstruktor wird verwendet wenn die Pixeldaten, Höhe und Breite
 * 			der Textur bereits bekannt sind.
 * 
 * @see LevelManager::load()
 * 
 * @param data Zeiger auf die Pixeldaten
 * @param width Breite der Bitmap
 * @param height Höhe der Bitmap
 */
Texture::Texture(char* data, uint width, uint height) {
	_width = width;
	_height = height;
	GLuint textureId;
	generate(textureId, data);
}

/**
 * @brief Erstellt ein Objekt der Texturenklasse
 * @details Buffert die Bitmap, liest benötigte Informationen aus
 * 			und erstellt eine OpenGL TextureID.
 * 
 * @param path Pfad zur Bitmap im Dateisystem
 * @param spriteCount Anzahl der Sprites innerhalb der Textur
 */
Texture::Texture(const char* path, uint spriteCount) {
	buffer(path, spriteCount, &_width, &_height);
}

/**
 * @brief Generiert OpenGL TextureID
 * @details Erstellt aus der Breite, der Höhe und den Pixeldaten der Bitmap
 * 			eine TextureID für OpenGL und wendet verschiedene Parameter auf
 * 			sie an.
 * 			Fügt auch die TextureID in die Liste der Sprites für eventuelle
 * 			Animationen ein und gibt den Speicher der Pixeldaten wieder frei.
 */
void Texture::generate(GLuint textureId, char* data) {
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
	
	_spriteList.push_back(textureId);
	free(data);
}

/**
 * @brief Wertet Bitmap aus und liefert Pixeldaten und Informationen
 * @details Bitmap wird Byte für Byte ausgelesen. File Header und Information Header
 * 			werden zwischengespeichert um Breite und Höhe der Bitmap auszuwerten.
 * 			Bitmap wird in Abhängigkeit von der Anzahl der Sprites innerhalb der Textur
 * 			geteilt um Sprites für eine eventuelle Animation separat buffern zu können.
 * 
 * @see https://www.pohlig.de/Unterricht/Inf2004/Kap27/27.3_Das_bmp_Format.htm
 * 
 * @param path Pfad zur Bitmap im Dateisystem
 * @param spriteCount Anzahl der Sprites innerhalb der Textur
 * @param width Pointer auf die Breite der Bitmap (Rückgabe)
 * @param height Pointer auf die Höhe der Bitmap (Rückgabe)
 */
void Texture::buffer(const char* path, uint spriteCount, uint* width, uint* height) {
	std::ifstream file;
	file.open(path, std::ios::out | std::ios::binary);
	
	if(!file.is_open()) {
		std::cout << "Could not open file \"" << path << "\"." << std::endl;
		exit(1);
	}
	
	char fileHeader[FILE_HEADER_SIZE];
	file.read(fileHeader, FILE_HEADER_SIZE);
	
	int dataOffset = byte_to_int16(fileHeader, 10);
	
	char informationHeader[INFORMATION_HEADER_SIZE];
	file.read(informationHeader, INFORMATION_HEADER_SIZE);
	
	file.ignore(dataOffset - FILE_HEADER_SIZE - INFORMATION_HEADER_SIZE);
	
	*width = byte_to_int16(informationHeader, 4);
	*height = byte_to_int16(informationHeader, 8);
	
	uint spriteHeight = *height / spriteCount;
	*height = spriteHeight;
	
	int spriteDataSize = *width * *height * 4;
	
	for(int i = 0; i < spriteCount; i++) {
		char* data = (char*)malloc(spriteDataSize);
		file.read(data, spriteDataSize);
		
		GLuint textureId;
		generate(textureId, data);
	}
	
	file.close();
}

/**
 * @brief Gibt Breite der Textur zurück
 * 
 * @return Breite
 */
uint Texture::getWidth() const {
	return _width;
}

/**
 * @brief Gibt Höhe der Textur zurück
 * 
 * @return Höhe
 */
uint Texture::getHeight() const {
	return _height;
}

void Texture::setAnimationType(AnimationType type) {
	_animationType = type;
}

void Texture::toggleAnimation(bool running) {
	_animationRunning = running;
}

/**
 * @brief Gibt nächste TextureID (der Animation) zurück
 * 
 * @return TextureID
 */
GLuint Texture::next() {
	uint spriteCount = _spriteList.size();

	if(_animationType == AnimationType::STATIC) {
		return _spriteList[spriteCount - 1];
	}

	if(_animationType == AnimationType::ONCE) {
		if(_animationRunning && _currentSprite < spriteCount) {
			_currentSprite += 1;
		}
		return _spriteList[spriteCount - _currentSprite - 1];
	}

	if(_animationType == AnimationType::REPEAT) {
		_currentSprite += 1;
		if(_currentSprite >= spriteCount * 10) {
			_currentSprite = 0;
		}
		return _spriteList[spriteCount - _currentSprite/10 - 1];
	}
}