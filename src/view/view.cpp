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
	buffer(std::make_unique<Player>(), 4);
	buffer(std::make_unique<Rocket>(), 1);
	buffer(std::make_unique<Missile>(), 1);
}

/**
 * @brief Buffert Drawable Objekte
 * @details Sucht die zugehörige Bitmap im Dateisystem und
 * 			erstellt ein Objekt der Texturenklasse.
 * 
 * @param object Drawable Objekt
 */
void View::buffer(std::shared_ptr<Drawable> object, uint spriteCount) {
	auto info = object->getRenderInformation();
	auto file = "./assets/" + info.identifier + ".bmp";
	auto texture = std::make_shared<Texture>(file.c_str(), spriteCount);
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
	_textureBuffer[info.identifier] = texture;
	
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
	_vertexBuffer[info.identifier] = vertexBufferId;
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
	
	auto textureId = _textureBuffer[info.identifier]->next();
	glBindTexture(GL_TEXTURE_2D, textureId);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));
	
	auto vertexId = _vertexBuffer[info.identifier];
	glBindBuffer(GL_ARRAY_BUFFER, vertexId);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, positionCoordinates));
	
	glDrawArrays(GL_QUADS, 0, 4);
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