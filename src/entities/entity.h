#ifndef SCRAMBLE_ENTITY_H
#define SCRAMBLE_ENTITY_H

#include "../utils/base.h"
#include "../utils/const.h"
#include "../physics/object.h"
#include "../physics/physics.h"

#include <vector>

#include "../view/drawable.h"
#include "../utils/vector2.h"

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
		Vector2 _size;
		Vector2 _position;
		Vector2 _velocity;
		uint _speed;
		int _rotation;
		virtual void update() = 0;
	public:
		Entity();
		void updateEntity();
		virtual void onCollision(std::shared_ptr<Entity>) = 0;
		EntityType getType();
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
		RenderInformation getRenderInformation();
};

#endif //SCRAMBLE_ENTITY_H