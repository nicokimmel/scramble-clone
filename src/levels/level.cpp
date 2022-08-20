#include "level.h"

/**
 * @brief Erstellt Objekt der Levelklasse
 * @details Wird vom LevelManager erstellt.
 * 			Enthält alle Informationen über das Level.
 * 
 * @see LevelManager::load()
 * 
 * @param LevelInformation info
 */
Level::Level(LevelInformation info) {
	_name = info.name;
	_width = info.width;
	_height = info.height;
	_scrollSpeed = info.scrollSpeed;
	_player = info.player;
	_sky = info.sky;
	_entityList = info.entityList;
	_collisionMap = info.collisionMap;
	_offset = 0;
}

/**
 * @brief Updatefunktion des Levels
 * @details Wird jede Iteration der Gameloop aufgerufen.
 */
void Level::update() {
	_offset += _scrollSpeed;
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
 * @brief Gibt Identifier des Levels zurück
 * @details Dieser ist immer 99 für alle Levels.
 * 			Die View nutzt diese Funktion um Texturen
 * 			je nach Entitätentyp einzulesen.
 * 
 * @see Drawable
 * @see View
 * 
 * @return int 
 */
int Level::getIdentifier() {
	return 99;
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
 * @brief Gibt die Größe des Levels zurück
 * @details Das Level ist um 50% komprimiert um die
 * 			Zeit zum Einlesen zu verkürzen, weshalb
 * 			Höhe und Breite verdoppelt werden.
 * 			So füllt es nach dem Zeichnen der View
 * 			wieder das komplette Fenster aus.
 * 
 * @see Drawable
 * @see View
 * 
 * @return Vector2 
 */
Vector2 Level::getSize() {
	return Vector2(_width * 2, _height * 2);
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
 * @brief Gibt die Position des Levels zurück
 * @details Gleichbedeutend wie der negative Offset.
 * 			Muss wegen des Drawable Interfaces
 * 			implementiert werden.
 * 
 * @see Drawable
 * @see View
 * 
 * @return Vector2 Position
 */
Vector2 Level::getPosition() {
	return Vector2(-_offset, 0);
}

/**
 * @brief Gibt Bewegungsgeschwindigkeit des Levels zurück
 * @details Mit dieser Geschwindigkeit bewegen sich auch alle
 * 			Entitäten nach Links um einen Flug zu simulieren.
 * 
 * @return uint Bewegungsgeschwindigkeit 
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

/**
 * @brief Gibt die Rotation des Levels zurück
 * @details Diese ist immer 0; Die Funktion muss allerdings
 * 			durch das Drawable Interface implementiert werden.
 * 
 * @see Drawable
 * @see View
 * 
 * @return int Rotation
 */
int Level::getRotation() {
	return 0;
}

/**
 * @brief Erstellt eine Entität je nach Typ
 * 
 * @param type Entitätentyp
 * @return std::shared_ptr<Entity> Entität
 */
std::shared_ptr<Entity> Level::spawn(EntityType type) {
	std::shared_ptr<Entity> entity;
	
	switch(type) {
		case EntityType::MISSILE:
			entity = std::make_shared<Missile>();
			entity->setPosition(_player->getPosition().add(Vector2(_player->getSize().getX() / 2 - entity->getSize().getX() / 2, -_player->getSize().getY() / 2)));
			break;
		case EntityType::LASER:
			entity = std::make_shared<Laser>();
			entity->setPosition(_player->getPosition().add(Vector2(_player->getSize().getX() - 10, _player->getSize().getY() / 2 - entity->getSize().getY() / 2)));
			break;
	}
	
	entity->setVelocity(entity->getVelocity() + Vector2(-_scrollSpeed, 0));
	
	_entityList.push_back(entity);
	return entity;
}

/**
 * @brief Löscht eine Entität
 * 
 * @param target Zielentität
 */
void Level::despawn(std::shared_ptr<Entity> target) {
	auto iterator = std::find_if(_entityList.begin(), _entityList.end(), [&](const std::shared_ptr<Entity> entity) { return entity == target; });
	_entityList.erase(iterator);
}

/**
 * @brief Lässt eine Entität explodieren
 * @details Löscht die Zielentität und erstellt eine neue Entität
 * 			vom Typ "Explosion". Dieser bekommt je nach Entitätentyp
 * 			einen anderen Explosionstypen.
 * 			Wird an der gleichen Position erstellt.
 * 
 * @param target 
 * @return std::shared_ptr<Entity> 
 */
std::shared_ptr<Entity> Level::explode(std::shared_ptr<Entity> target) {
	auto pos = Vector2(target->getPosition().getX() + target->getSize().getX() / 2, target->getPosition().getY() + target->getSize().getY() / 2);
	
	despawn(target);
	
	std::shared_ptr<Explosion> explosion;
	if(target->getType() == EntityType::PLAYER) {
		explosion = std::make_shared<Explosion>(ExplosionType::EPLAYER);
	} else {
		explosion = std::make_shared<Explosion>(ExplosionType::EDEFAULT);
	}
	
	pos = Vector2(pos.getX() - explosion->getSize().getX() / 2, pos.getY() - explosion->getSize().getY() / 2);
	explosion->setPosition(pos);
	
	explosion->setVelocity(Vector2(-_scrollSpeed, 0));
	
	_entityList.push_back(explosion);
	return explosion;
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
 * @brief Gibt die Himmelentität zurück
 * 
 * @return std::shared_ptr<Sky> Sternenhimmel
 */
std::shared_ptr<Sky> Level::getSky() {
	return _sky;
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
 * @brief Gibt Pointer auf Entitätenliste zurück
 * 
 * @return Pointer auf Entitätenliste
 */
std::vector<std::shared_ptr<Object>> Level::getObjectList() {
	std::vector<std::shared_ptr<Object>> entityList = std::vector<std::shared_ptr<Object>>();
	for(auto entity : _entityList) {
		entityList.push_back(entity);
	}
	return entityList;
}

/**
 * @brief Gibt den Transparenzwert an Pixel X/Y aus.
 * @details Damit kann eine pixelgenaue Kollision
 * 			abgefragt werden.
 * 
 * @see Physics
 * 
 * @param x X-Koodinate
 * @param y Y-Koodinate
 * @return int Transparenzwert
 */
int Level::getAlpha(int x, int y) {
	if(x < 0) {
		x = 0;
	}
	if(y < 0) {
		y = 0;
	}

	x += _offset;

	x = x/2;
	y = y/2;
	
	int index = y * _width + x;
	return (index < 0 || index > _collisionMap.size() - 1) ? 0 : _collisionMap[index];
}