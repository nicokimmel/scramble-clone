#include "../src/entities/missile.h"

int main(int argc, char** argv) {
	
	auto missile = std::make_unique<Missile>();
		
	/**
	 * Missile kollidiert mit der Welt.
	 * 
	 * Erwartung:	_crashed wird auf TRUE gesetzt.
	 */
	missile->onCollision(EntityType::NONE);
	assert(missile->hasCrashed() == true);
	
	
	/**
	 * Missile Update.
	 * 
	 * Erwartung:	_rotation ändert sich nach update.
	 * 	    		_velocity ändert sich nach update.
	 */
	auto oldRotation = missile->getRotation();
	auto oldVelocity = missile->getVelocity();
	for(int i = 400 ; i >= 0 ; i--) {
		missile->update();
	}
	auto newRotation = missile->getRotation();
	auto newVelocity = missile->getVelocity();
	assert(newRotation != oldRotation);
	assert(oldVelocity.getX() != newVelocity.getX());

	return 0;
}