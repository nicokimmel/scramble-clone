#include "level.h"

/**
 * @brief Erstellt Objekt der Levelklasse
 * @details Wird vom LevelManager aufgerufen.
 * 			Enthält alle Informationen über das Level.
 * 
 * @see LevelManager::load()
 * 
 * @param name Name des Levels
 * @param width Breite des Levels
 * @param height Höhe des Levels
 * @param scrollSpeed Bewegungsgeschwindigkeit
 * @param player Pointer auf Spielerobjekt
 * @param entityList Liste aller Entitäten
 */
Level::Level(std::string name, uint width, uint height, uint scrollSpeed, std::shared_ptr<Player> player, std::vector<std::shared_ptr<Entity>> entityList, int collisionMap[]) {
	_name = name;
	_width = width;
	_height = height;
	_scrollSpeed = scrollSpeed;
	_player = player;
	_entityList = entityList;
	_collisionMap = collisionMap;
	_offset = 0;
}

/**
 * @brief Updatefunktion des Levels
 * @details Wird jede Iteration der Gameloop aufgerufen.
 */
void Level::update() {
	_offset += _scrollSpeed;
	if(_offset >= (_width - WINDOW_WIDTH)) {
		_offset = 0;
	}
}

/**
 * @brief Gibt Levelnamen zurück
 * 
 * @return Levelname 
 */
std::string Level::getName() const {
	return _name;
}

/**
 * @brief Gibt Breite des Levels zurück
 * 
 * @return Levelbreite 
 */
uint Level::getWidth() const {
	return _width;
}

/**
 * @brief Gibt Höhe des Levels zurück
 * 
 * @return Levelhöhe 
 */
uint Level::getHeight() const {
	return _height;
}

/**
 * @brief Gibt Offset des Levels zurück
 * @details Linksverschiebung des Levels
 * 
 * @return Leveloffset 
 */
uint Level::getOffset() {
	return _offset;
}

/**
 * @brief Setzt Offset des Levels
 * @details Linksverschiebung des Levels
 * 
 * @param offset Leveloffset
 */
void Level::setOffset(uint offset) {
	_offset = offset;
}

/**
 * @brief Gibt Bewegungsgeschwindigkeit des Levels zurück
 * @details Mit dieser Geschwindigkeit bewegen sich auch alle
 * 			Entitäten nach Links um einen Flug zu simulieren.
 * 
 * @return Bewegungsgeschwindigkeit 
 */
uint Level::getScrollSpeed() {
	return _scrollSpeed;
}

/**
 * @brief Setzt Bewegungsgeschwindigkeit des Levels
 * @details Mit dieser Geschwindigkeit bewegen sich auch alle
 * 			Entitäten nach Links um einen Flug zu simulieren.
 * 
 * @param scrollSpeed Bewegungsgeschwindigkeit
 */
void Level::setScrollSpeed(uint scrollSpeed) {
	_scrollSpeed = scrollSpeed;
}

void Level::spawn() {
	auto missile = std::make_shared<Missile>();
	auto pos = _player->getPosition();
	pos = pos.add(Vector2(_player->getSize().getX() / 2 - missile->getSize().getX() / 2, -_player->getSize().getY() / 2));
	missile->setPosition(pos);
	_entityList.push_back(missile);
}

void Level::despawn(std::shared_ptr<Entity> entity) {
	for(auto entity : _entityList) {
		std::remove(_entityList.begin(), _entityList.end(), entity);
	}
}

/**
 * @brief Iteriert über alle Entitäten
 * @details Ruft übergebenen Callback mit Entität als Übergabeparameter auf.
 * 
 * @param func Callback welcher für jede Entität aufgerunfen wird
 */
void Level::iterate(entityCallback func) {
	for(auto entity : _entityList) {
		std::invoke(func, entity);
	}
}

/**
 * @brief Gibt Pointer auf Spielerobjekt zurück
 * 
 * @return Pointer auf Spielerobjekt
 */
std::shared_ptr<Player> Level::getPlayer() {
	return _player;
}

/**
 * @brief Gibt Pointer auf Entitätenliste zurück
 * 
 * @return Pointer auf Entitätenliste
 */
std::vector<std::shared_ptr<Entity>> Level::getEntityList() {
	return _entityList;
}

/**
 * @brief Gibt Informationen zum Zeichnen des Levels zurück
 * @details Der Identifikator ist der Levelname, die Position
 * 			bildet hier das Offset des Levels.
 * 
 * @return Informationen zum Zeichnen 
 */
RenderInformation Level::getRenderInformation() {
	RenderInformation info;
	info.identifier = _name;
	info.width = _width * 2;
	info.height = _height * 2;
	info.x = _offset * -1;
	info.y = 0;
	info.rotation = 0;
	return info;
}

int Level::getCollisionMap(int x, int y) {
	if(x < 0) {
		x = 0;
	}
	if(y < 0) {
		y = 0;
	}
	x += _offset;
	return _collisionMap[y * _width + x];
}