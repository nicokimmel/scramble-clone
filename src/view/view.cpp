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
	SpriteInformation sp;
	
	sp.animationType = AnimationType::REPEAT;
	sp.spriteCount = 4;
	sp.spriteFile = "./assets/player.bmp";
	_spriteList["player"] = sp;
	
	/*sp.animationType = AnimationType::ONCE;
	sp.spriteCount = 7;
	sp.spriteFile = "./assets/player-explosion.bmp";
	_spriteList["player"] = sp;*/
	
	sp.animationType = AnimationType::STATIC;
	sp.spriteCount = 1;
	sp.spriteFile = "./assets/laser.bmp";
	_spriteList["laser"] = sp;
	
	sp.animationType = AnimationType::ONCE;
	sp.spriteCount = 6;
	sp.spriteFile = "./assets/missile.bmp";
	_spriteList["missile"] = sp;
	
	sp.animationType = AnimationType::ONCE;
	sp.spriteCount = 2;
	sp.spriteFile = "./assets/rocket.bmp";
	_spriteList["rocket"] = sp;
	
	sp.animationType = AnimationType::STATIC;
	sp.spriteCount = 1;
	sp.spriteFile = "./assets/building.bmp";
	_spriteList["building"] = sp;
	
	sp.animationType = AnimationType::STATIC;
	sp.spriteCount = 1;
	sp.spriteFile = "./assets/fuel.bmp";
	_spriteList["fuel"] = sp;
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
	glRotatef(info.rotation, 0.0f, 0.0f, -1.0f);
	
	auto textureId = _textureBuffer[object]->get();
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