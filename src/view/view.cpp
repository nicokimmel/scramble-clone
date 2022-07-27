#include "view.h"

/**
 * @brief Erstellt Objekt der View Klasse
 * @details Initialisiert auch GLFW und GLEW und erstellt
 * 			ein Fenster in dem anschließend gezeichnet wird.
 * 			Setzt auch einige OpenGL Werte.
 */
View::View() {
	glfwInit();
	_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Scramble Clone", NULL, NULL);
	glfwMakeContextCurrent(_window);
	
	glewInit();
	
	glViewport(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	//glfwSwapInterval(0);
}

/**
 * @brief Buffert Texturen für Entities
 * 
 * @todo Auslagern
 */
void View::init() {
	_spriteList["player"] = SpriteInformation(AnimationType::REPEAT, 4, "./assets/player.bmp");
	_spriteList["laser"] = SpriteInformation(AnimationType::STATIC, 1, "./assets/laser.bmp");
	_spriteList["rocket"] = SpriteInformation(AnimationType::ONCE, 2, "./assets/rocket.bmp");
	_spriteList["building"] = SpriteInformation(AnimationType::STATIC, 1, "./assets/building.bmp");
	_spriteList["fuel"] = SpriteInformation(AnimationType::STATIC, 1, "./assets/fuel.bmp");
}

/**
 * @brief Buffert Drawable Objekte
 * @details Sucht die zugehörige Bitmap im Dateisystem und
 * 			erstellt ein Objekt der Texturenklasse.
 * 
 * @param object Drawable Objekt
 */
void View::buffer(std::shared_ptr<Drawable> object) {
	auto info = object->getRenderInformation();
	auto spriteFile = _spriteList[info.identifier].spriteFile;
	auto spriteCount = _spriteList[info.identifier].spriteCount;
	auto texture = std::make_shared<Texture>(spriteFile.c_str(), spriteCount);
	auto animationType = _spriteList[info.identifier].animationType;
	texture->setAnimationType(animationType);
	buffer(object, texture);
}

/**
 * @brief Buffert Drawable Objekte
 * @details Wird verwendet, wenn bereits ein Objekt der Texturenklasse
 * 			vorliegt. Erstellt Buffer für Vertices des Objektes und speichert
 * 			TextureID und VertexID in eine Hilfsliste.
 * 
 * @param object 
 * @param texture 
 */
void View::buffer(std::shared_ptr<Drawable> object, std::shared_ptr<Texture> texture) {
	auto info = object->getRenderInformation();
	_textureBuffer[object] = texture;
	
	Vertex vertices[] = {
		{{0.0f, 0.0f, 0.0f},				{0.0f, 0.0f}},
		{{info.width, 0.0f, 0.0f},			{1.0f, 0.0f}},
		{{info.width, info.height, 0.0f},	{1.0f, 1.0f}},
		{{0.0f, info.height, 0.0f},			{0.0f, 1.0f}}
	};
	
	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	_vertexBuffer[object] = vertexBufferId;
}

/**
 * @brief Zeichnet Drawable Objekt in OpenGL Fenster
 * 
 * @param object Drawable Objekt
 */
void View::render(std::shared_ptr<Drawable> object) {
	auto info = object->getRenderInformation();
	
	glLoadIdentity();
	glTranslatef(info.x, info.y, 0);
	
	auto textureId = _textureBuffer[object]->next();
	glBindTexture(GL_TEXTURE_2D, textureId);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));
	
	auto vertexId = _vertexBuffer[object];
	glBindBuffer(GL_ARRAY_BUFFER, vertexId);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, positionCoordinates));
	
	glDrawArrays(GL_QUADS, 0, 4);
}

void View::startAnimation(std::shared_ptr<Drawable> drawable) {
	_textureBuffer[drawable]->toggleAnimation(true);
}

void View::stopAnimation(std::shared_ptr<Drawable> drawable) {
	_textureBuffer[drawable]->toggleAnimation(false);
}

/**
 * @brief Überzeichnet aktuellen OpenGL Buffer
 */
void View::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * @brief Vertauscht OpenGL Buffer und zeigt gezeichnetes Bild
 */
void View::flip() {
	glfwSwapBuffers(_window);
}

/**
 * @brief Gibt Pointer auf Fenster zurück
 * 
 * @return Pointer auf Fenster 
 */
GLFWwindow* View::getWindow() {
	return _window;
}

/**
 * @brief Gibt zurück, ob das Fenster noch offen ist
 * @details Wird verwendet um die GameLoop zu stoppen, falls das
 * 			Fenster geschlossen wird.
 * 
 * @see Controller::start()
 * 
 * @return true 
 * @return false 
 */
bool View::isWindowOpen() {
	return !glfwWindowShouldClose(_window);
}