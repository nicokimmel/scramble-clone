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
class Entity : public Drawable, public Object {
	protected:
		std::shared_ptr<Physics> _physics;
		EntityType _type;
		Vector2 _size;
		Vector2 _position;
		Vector2 _velocity;
		uint _speed;
		int _rotation;
		bool _crashed;
		virtual void update() = 0;
	public:
		Entity();
		void updateEntity();
		EntityType getType();
		int getIdentifier();
		Vector2 getSize();
		void setSize(Vector2);
		Vector2 getPosition();
		void setPosition(Vector2);
		Vector2 getVelocity();
		void setVelocity(Vector2);
		uint getSpeed();
		void setSpeed(uint);
		int getRotation();
		void setRotation(int);
		bool hasCrashed();
};

#endif //SCRAMBLE_ENTITY_H