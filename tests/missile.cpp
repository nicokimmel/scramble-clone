#include "../src/entities/missile.h"

int main(int argc, char** argv) {
	
	auto missile = std::make_unique<Missile>();
	
	
	/**
	 * Test:		Missile kollidiert mit der Welt.
	 * 
	 * Erwartung:	_crashed wird auf TRUE gesetzt.
	 */
	missile->onCollision(EntityType::NONE);
	assert(missile->hasCrashed() == true);
	
	
	/**
	 * Test:		Missile Update wird von
	 * 				GameLoop aufgerufen.
	 * 
	 * Erwartung:	Rotation und Velocity ändern
	 * 				sich, da die Missile losfliegt.
	 */
	auto oldRot = missile->getRotation();
	auto oldVel = missile->getVelocity();
	for(int i = 0; i <= 400; i++) {
		missile->update();
	}
	assert(oldRot != missile->getRotation());
	assert(oldVel != missile->getVelocity());
	
	
	return 0;
}