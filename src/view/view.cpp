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
 * 
 * @todo Auslagern
 */
void View::init() {
	SpriteInformation sp;
	
	sp.animationType = AnimationType::REPEAT;
	sp.spriteCount = 4;
	sp.spriteFile = "./assets/player.bmp";
	_spriteList[EntityType::PLAYER] = sp;
	
	sp.animationType = AnimationType::STATIC;
	sp.spriteCount = 1;
	sp.spriteFile = "./assets/laser.bmp";
	_spriteList[EntityType::LASER] = sp;
	
	sp.animationType = AnimationType::ONCE;
	sp.spriteCount = 6;
	sp.spriteFile = "./assets/missile.bmp";
	_spriteList[EntityType::MISSILE] = sp;
	
	sp.animationType = AnimationType::ONCE;
	sp.spriteCount = 3;
	sp.spriteFile = "./assets/rocket.bmp";
	_spriteList[EntityType::ROCKET] = sp;
	
	sp.animationType = AnimationType::STATIC;
	sp.spriteCount = 1;
	sp.spriteFile = "./assets/building.bmp";
	_spriteList[EntityType::BUILDING] = sp;
	
	sp.animationType = AnimationType::STATIC;
	sp.spriteCount = 1;
	sp.spriteFile = "./assets/fuel.bmp";
	_spriteList[EntityType::FUEL] = sp;
	
	sp.animationType = AnimationType::REPEAT;
	sp.spriteCount = 4;
	sp.spriteFile = "./assets/explosion-default.bmp";
	_spriteList[ExplosionType::EDEFAULT] = sp;
	
	sp.animationType = AnimationType::REPEAT;
	sp.spriteCount = 7;
	sp.spriteFile = "./assets/explosion-player.bmp";
	_spriteList[ExplosionType::EPLAYER] = sp;
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
		{{0.0f, 0.0f, 0.0f},				{0.0f, 0.0f}},
		{{size.getX(), 0.0f, 0.0f},			{1.0f, 0.0f}},
		{{size.getX(), size.getY(), 0.0f},	{1.0f, 1.0f}},
		{{0.0f, size.getY(), 0.0f},			{0.0f, 1.0f}}
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
 * @brief Callbackfunktion für Animationen
 * @details Wird innerhalb einer registerUpdate() alle 150ms
 * 			aufgerufen um die Animation aller Entitäten zu
 * 			aktualisieren
 * 
 * @see Controller
 * @see EventManager
 */
void View::tick() {
	for(auto entry : _textureBuffer) {
		entry.second->next();
	}
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