#ifndef SCRAMBLE_LEVELMANAGER_H
#define SCRAMBLE_LEVELMANAGER_H

#define LEVEL_HEADER_SIZE 18
#define LEVEL_ENTITY_SIZE 12

#include "../utils/base.h"
#include "../utils/bytes.h"

#include <vector>

#include "level.h"
#include "../view/view.h"
#include "../entities/entity.h"
#include "../entities/player.h"
#include "../entities/rocket.h"
#include "../entities/fuel.h"
#include "../entities/building.h"
#include "../entities/sky.h"

/**
 * @brief Lädt Level vom Dateisystem und generiert Levelobjekte
 */
class LevelManager {
	private:
		std::shared_ptr<View> _view;
	public:
		LevelManager(std::shared_ptr<View>);
		std::shared_ptr<Level> load(std::string levelName);
};

#endif //SCRAMBLE_LEVELMANAGER_H