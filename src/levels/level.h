#ifndef SCRAMBLE_LEVEL_H
#define SCRAMBLE_LEVEL_H

#include "../utils/base.h"

#include <functional>
#include <vector>

#include "../view/drawable.h"
#include "../physics/world.h"
#include "../entities/player.h"
#include "../entities/missile.h"
#include "../entities/laser.h"
#include "../entities/explosion.h"
#include "../entities/sky.h"

typedef std::function<void(std::shared_ptr<Entity>)> entityCallback;

struct LevelInformation {
	std::string name;
	uint width;
	uint height;
	uint scrollSpeed;
	std::shared_ptr<Player> player;
	std::shared_ptr<Sky> sky;
	std::vector<std::shared_ptr<Entity>> entityList;
	std::vector<int> collisionMap;
};

/**
 * @brief Hält Informationen über ein Level
 * @details Levelobjekte werden vom LevelManager erstellt.
 * 			Erbt von Drawable, damit die View das Level
 * 			zeichnen kann.
 * 
 * @see LevelManager::load()
 */
class Level : public Drawable, public World {
	protected:
		std::string _name;
		uint _width;
		uint _height;
		uint _scrollSpeed;
		std::shared_ptr<Player> _player;
		std::shared_ptr<Sky> _sky;
		std::vector<std::shared_ptr<Entity>> _entityList;
		std::vector<int> _collisionMap;
		uint _offset;
	public:
		Level(LevelInformation);
		void update();
		std::string getName() const;
		int getIdentifier();
		uint getWidth() const;
		uint getHeight() const;
		Vector2 getSize();
		uint getOffset();
		void setOffset(uint);
		Vector2 getPosition();
		uint getScrollSpeed();
		void setScrollSpeed(uint);
		int getRotation();
		std::shared_ptr<Entity> spawn(EntityType type);
		void despawn(std::shared_ptr<Entity>);
		std::shared_ptr<Entity> explode(std::shared_ptr<Entity>);
		void iterate(entityCallback);
		std::shared_ptr<Player> getPlayer();
		std::shared_ptr<Sky> getSky();
		std::vector<std::shared_ptr<Entity>> getEntityList();
		std::vector<std::shared_ptr<Object>> getObjectList();
		int getAlpha(int, int);
};

#endif //SCRAMBLE_LEVEL_H