#include "../src/entities/player.h"
#include "../src/entities/laser.h"

int main(int argc, char** argv) {
	
	auto player = std::make_shared<Player>();
	
	/**
	 * Spieler kollidiert mit seinem eigenen Laser.
	 * 
	 * Erwartung:	Leben bleibt auf 3, Raumschiff stürzt
	 * 				nicht ab.
	 */
	player->onCollision(EntityType::LASER);
	assert(player->getLives() == 3);
	assert(player->hasCrashed() == false);
	
	    
	/**
	 * Spieler kollidiert mit der Welt.
	 * 
	 * Erwartung:	Leben werden von 3 auf 2 verringert
	 * 				und _crashed wird auf TRUE gesetzt.
	 */
	player->onCollision(EntityType::NONE);
	assert(player->getLives() == 2);
	assert(player->hasCrashed() == true);
	
	
	/**
	 * Spieler bewegt sich nach oben.
	 * 
	 * Erwartung:	Y-Koordinate des Spielers wird um
	 * 				seine Geschwindigkeit erhöht.
	 * 				X-Koordinate bleibt dabei gleich.
	 */
	auto oldPos = player->getPosition();
	player->moveUp();
	auto newPos = player->getPosition();
	assert(newPos.getX() == oldPos.getX());
	assert(newPos.getY() == oldPos.getY() + player->getSpeed());
	
	
	/**
	 * Leben des Spielers wird auf 5 gesetzt.
	 * 
	 * Erwartung:	Spieler hat 5 Leben.
	 */
	player->setLives(5);
	assert(player->getLives() == 5);
	
	
	/**
	 * Treibstoff des Spielers wird über die maximale
	 * Menge erhöht.
	 * 
	 * Erwartung:	Treibstoff wird nur auf 100 gesetzt.
	 */
	player->addFuel(150);
	assert(player->getFuel() == 100);
	
	
	/**
	 * Treibstoff des Spielers wird auf 0 gesetzt.
	 * Anschließend tickt das onFuel() Event.
	 * 
	 * Erwartung:	Treibstoff wird auf 0 gesetzt.
	 * 				Geschwindigkeit des Spielers wird
	 * 				auf 0 und Velocity auf 2, -2 gesetzt.
	 */
	player->setFuel(0);
	assert(player->getFuel() == 0);
	player->onFuel();
	assert(player->getSpeed() == 0);
	assert(player->getVelocity() == Vector2(2, -2));
	
	return 0;
}