#ifndef SCRAMBLE_VIEW_H
#define SCRAMBLE_VIEW_H

#include "../utils/base.h"

#include <filesystem>
#include <map>

#include "../textures/texture.h"
#include "../entities/entity.h"
#include "../entities/rocket.h"
#include "../entities/fuel.h"
#include "../levels/level.h"

/**
 * @brief Hält Vertices und Texturkoordinaten
 */
struct Vertex {
	GLfloat positionCoordinates[3];
	GLfloat textureCoordinates[2];
};

/**
 * @brief Verwaltet OpenGL Fenster und zeichnet Drawable Objekte
 * @details Buffert Drawable Objekte und speichert dessen Vertices,
 * 			Texturkoordinaten und TextureIDs in Hilfslisten.
 * 			Spielt auch Animationen ab und startet/stoppt diese.
 */
class View {
	private:
		GLFWwindow* _window;
		std::map<std::shared_ptr<Drawable>, std::shared_ptr<Texture>> _textureBuffer;
		std::map<std::shared_ptr<Drawable>, GLuint> _vertexBuffer;
		std::map<int, SpriteInformation> _spriteList;
	public:
		View();
		void init();
		void buffer(std::shared_ptr<Drawable>);
		void buffer(std::shared_ptr<Drawable>, std::shared_ptr<Texture>);
		void render(std::shared_ptr<Drawable>);
		void startAnimation(std::shared_ptr<Drawable>);
		void stopAnimation(std::shared_ptr<Drawable>);
		void clear();
		void flip();
		void tick();
		GLFWwindow* getWindow();
		bool isWindowOpen();
};

#endif //SCRAMBLE_VIEW_H