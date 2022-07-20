#ifndef SCRAMBLE_ENTITY_H
#define SCRAMBLE_ENTITY_H

#include "../utils/base.h"
#include "../utils/const.h"

#include <vector>

#include "../view/drawable.h"
#include "../utils/vector2.h"

enum EntityType {
	NONE, PLAYER, ROCKET, UFO, METOR, FUEL, BASE
};

static std::string EntityName[] = {
	"none", "player", "rocket", "ufo", "meteor", "fuel", "base"
};

class Entity : public Drawable {
	protected:
		EntityType _type;
		Vector2 _size;
		Vector2 _position;
		Vector2 _velocity;
		uint _speed;
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
		RenderInformation getRenderInformation();
};

#endif //SCRAMBLE_ENTITY_H