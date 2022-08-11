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
}

/**
 * @brief Gibt Levelnamen zurück
 * 
 * @return Levelname 
 */
std::string Level::getName() const {
	return _name;
}

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

Vector2 Level::getPosition() {
	return Vector2(-_offset, 0);
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

int Level::getRotation() {
	return 0;
}

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
	
	entity->setVelocity(entity->getVelocity().add(Vector2(-_scrollSpeed, 0)));
	
	_entityList.push_back(entity);
	return entity;
}

void Level::despawn(std::shared_ptr<Entity> target) {
	auto iterator = std::find_if(_entityList.begin(), _entityList.end(), [&](const std::shared_ptr<Entity> entity) { return entity == target; });
	_entityList.erase(iterator);
}

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
 * @brief Gibt Pointer auf Entitätenliste zurück
 * 
 * @return Pointer auf Entitätenliste
 */
std::vector<std::shared_ptr<Entity>> Level::getEntityList() {
	return _entityList;
}

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
	
	return _collisionMap[y * _width + x];
}