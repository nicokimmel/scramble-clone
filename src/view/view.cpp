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
 * @brief Initialisierung der View
 */
void View::init() {
	_spriteList[EntityType::PLAYER] = SpriteInformation(AnimationType::REPEAT, 4, "./assets/player.bmp");
	_spriteList[EntityType::LASER] = SpriteInformation(AnimationType::STATIC, 1, "./assets/laser.bmp");
	_spriteList[EntityType::MISSILE] = SpriteInformation(AnimationType::ONCE, 6, "./assets/missile.bmp");
	_spriteList[EntityType::ROCKET] = SpriteInformation(AnimationType::ONCE, 3, "./assets/rocket.bmp");
	_spriteList[EntityType::BUILDING] = SpriteInformation(AnimationType::STATIC, 1, "./assets/building.bmp");
	_spriteList[EntityType::FUEL] = SpriteInformation(AnimationType::STATIC, 1, "./assets/fuel.bmp");
	_spriteList[ExplosionType::EDEFAULT] = SpriteInformation(AnimationType::REPEAT, 4, "./assets/explosion-default.bmp");
	_spriteList[ExplosionType::EPLAYER] = SpriteInformation(AnimationType::REPEAT, 7, "./assets/explosion-player.bmp");
	_spriteList[EntityType::SKY] = SpriteInformation(AnimationType::REPEAT, 4, "./assets/sky.bmp");
}

/**
 * @brief Buffert Drawable Objekte
 * @details Sucht die zugehörige Bitmap im Dateisystem und
 * 			erstellt ein Objekt der Texturenklasse.
 * 
 * @param drawable Drawable Objekt
 */
void View::buffer(std::shared_ptr<Drawable> drawable) {
	int identifier = drawable->getIdentifier();
	
	auto spriteFile = _spriteList[identifier].spriteFile;
	auto spriteCount = _spriteList[identifier].spriteCount;
	auto texture = std::make_shared<Texture>(spriteFile.c_str(), spriteCount);
	auto animationType = _spriteList[identifier].animationType;
	texture->setAnimationType(animationType);
	buffer(drawable, texture);
}

/**
 * @brief Buffert Drawable Objekte
 * @details Wird verwendet, wenn bereits ein Objekt der Texturenklasse
 * 			vorliegt. Erstellt Buffer für Vertices des Objektes und speichert
 * 			TextureID und VertexID in eine Hilfsliste.
 * 
 * @param drawable
 * @param texture
 */
void View::buffer(std::shared_ptr<Drawable> drawable, std::shared_ptr<Texture> texture) {
	_textureBuffer[drawable] = texture;
	
	Vector2 size = drawable->getSize();
	
	Vertex vertices[] = {
		{{0.0f,			0.0f,		 0.0f},	{0.0f, 0.0f}},
		{{size.getX(),	0.0f,		 0.0f},	{1.0f, 0.0f}},
		{{size.getX(),	size.getY(), 0.0f},	{1.0f, 1.0f}},
		{{0.0f,			size.getY(), 0.0f},	{0.0f, 1.0f}}
	};
	
	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	_vertexBuffer[drawable] = vertexBufferId;
}

/**
 * @brief Zeichnet Drawable Objekt in OpenGL Fenster
 * 
 * @param drawable Drawable Objekt
 */
void View::render(std::shared_ptr<Drawable> drawable) {
	glLoadIdentity();
	
	Vector2 pos = drawable->getPosition();
	glTranslatef(pos.getX(), pos.getY(), 0);
	glRotatef(drawable->getRotation(), 0.0f, 0.0f, -1.0f);
	
	auto textureId = _textureBuffer[drawable]->get();
	glBindTexture(GL_TEXTURE_2D, textureId);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));
	
	auto vertexId = _vertexBuffer[drawable];
	glBindBuffer(GL_ARRAY_BUFFER, vertexId);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, positionCoordinates));
	
	glDrawArrays(GL_QUADS, 0, 4);
}

/**
 * @brief Startet Animation für Drawable Objekt
 * 
 * @param drawable Drawable Objekt
 */
void View::startAnimation(std::shared_ptr<Drawable> drawable) {
	_textureBuffer[drawable]->toggleAnimation(true);
}

/**
 * @brief Stoppt Animation für Drawable Objekt
 * 
 * @param drawable Drawable Objekt
 */
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
 * @brief Setzt nächstes Sprite als aktuelles Sprite für alle Entitäten
 * @details Lässt den Sternenhimmel aus, da dieser über die
 * 			überladene animate() Funktion manuell animiert wird.
 * 			Er besitzt eine langsamere Animation als der Rest.
 */
void View::animate() {
	for(auto entry : _textureBuffer) {
		if(entry.first->getIdentifier() == EntityType::SKY) {
			continue;
		}
		_textureBuffer[entry.first]->next();
	}
}

/**
 * @brief Setzt nächstes Sprite als aktuelles Sprite
 * 
 * @param drawable Drawable Objekt
 */
void View::animate(std::shared_ptr<Drawable> drawable) {
	_textureBuffer[drawable]->next();
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
 * @brief Gibt zurück, ob Fenster offen
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