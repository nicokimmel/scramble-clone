#include "../src/entities/missile.h"

int main(int argc, char** argv) {
	
	auto missile = std::make_unique<Missile>();
	
	/**
	 * Missile kollidiert mit der Welt.
	 * 
	 * Erwartung:	_crashed wird auf TRUE gesetzt.
	 */
	missile->onCollision(nullptr);
	assert(missile->hasCrashed() == true);
	
	
	return 0;
}