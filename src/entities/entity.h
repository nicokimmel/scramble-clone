#ifndef SCRAMBLE_ENTITY_H
#define SCRAMBLE_ENTITY_H

#include "../utils/base.h"
#include "../utils/const.h"

#include <vector>

#include "../view/drawable.h"
#include "../physics/object.h"
#include "../physics/physics.h"

enum EntityType {
	NONE, PLAYER, LASER, MISSILE, ROCKET, BUILDING, UFO, METEOR, FUEL, BASE
};

static std::string EntityName[] = {
	"none", "player", "laser", "missile", "rocket", "building", "ufo", "meteor", "fuel", "base"
};

class Entity : public Drawable, public Object {
	protected:
		std::shared_ptr<Physics> physics;
		EntityType _type;
		
		bool _crashed;
		virtual void update() = 0;
	public:
		Entity();
		void updateEntity();
		//virtual void onCollision(std::shared_ptr<Entity>) = 0;
		EntityType getType();
		
		bool hasCrashed();
		RenderInformation getRenderInformation();
};

#endif //SCRAMBLE_ENTITY_H