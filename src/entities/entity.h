#ifndef SCRAMBLE_ENTITY_H
#define SCRAMBLE_ENTITY_H

#include "../utils/base.h"
#include "../utils/const.h"

#include <vector>

#include "../view/drawable.h"
#include "../physics/object.h"
#include "../physics/physics.h"

enum EntityType {
	NONE, PLAYER, LASER, MISSILE, ROCKET, BUILDING, UFO, METEOR, FUEL, BASE, EXPLOSION
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
		EntityType getType();
		int getIdentifier();
		Vector2 getSize();
		Vector2 getPosition();
		int getRotation();
		bool hasCrashed();
};

#endif //SCRAMBLE_ENTITY_H