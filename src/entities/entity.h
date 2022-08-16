#ifndef SCRAMBLE_ENTITY_H
#define SCRAMBLE_ENTITY_H

#include "../utils/base.h"
#include "../utils/const.h"

#include <vector>

#include "../view/drawable.h"
#include "../physics/object.h"
#include "../physics/physics.h"

/**
 * @brief Arten der Entitäten
 */
enum EntityType {
	NONE, PLAYER, LASER, MISSILE, ROCKET, BUILDING, UFO, METEOR, FUEL, BASE, EXPLOSION
};

/**
 * @brief Überklasse aller im Spiel befindlichen Modellklassen
 */
class Entity : public Drawable, public Object, public std::enable_shared_from_this<Entity> {
	protected:
		std::shared_ptr<Physics> _physics;
		EntityType _type;
		bool _crashed;
		virtual void update() = 0;
		virtual void onCollision(EntityType) = 0;
	public:
		Entity();
		void updateEntity();
		void onCollision(std::shared_ptr<Object>);	
		EntityType getType();
		int getIdentifier();
		Vector2 getSize();
		Vector2 getPosition();
		int getRotation();
		bool hasCrashed();
};

#endif //SCRAMBLE_ENTITY_H