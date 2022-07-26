#ifndef SCRAMBLE_LEVEL_H
#define SCRAMBLE_LEVEL_H

#include "../utils/base.h"

#include <functional>
#include <vector>

#include "../view/drawable.h"
#include "../entities/player.h"

typedef std::function<void(std::shared_ptr<Entity>)> entityCallback;

/**
 * @brief Hält Informationen über ein Level
 * @details Levelobjekte werden vom LevelManager erstellt.
 * 			Erbt von Drawable, damit die View das Level
 * 			zeichnen kann.
 * 
 * @see LevelManager::load()
 */
class Level : public Drawable {
	protected:
		std::string _name;
		uint _width;
		uint _height;
		uint _scrollSpeed;
		std::shared_ptr<Player> _player;
		std::vector<std::shared_ptr<Entity>> _entityList;
		int* _collisionMap;
		uint _offset;
	public:
		Level(std::string, uint, uint, uint, std::shared_ptr<Player>, std::vector<std::shared_ptr<Entity>>, int[]);
		void update();
		std::string getName() const;
		uint getWidth() const;
		uint getHeight() const;
		uint getOffset();
		void setOffset(uint);
		uint getScrollSpeed();
		void setScrollSpeed(uint);
		void iterate(entityCallback);
		std::shared_ptr<Player> getPlayer();
		std::vector<std::shared_ptr<Entity>> getEntityList();
		int getAlpha(int, int);
		RenderInformation getRenderInformation();
};

#endif //SCRAMBLE_LEVEL_H