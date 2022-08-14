#include "explosion.h"

/**
 * @brief Erstellt Objekt von Explosion
 * @details Der Spieler hat eine andere Explosion
 * 			als andere Objekte.
 * 
 * @param explosionType Explosionstyp
 */
Explosion::Explosion(ExplosionType explosionType) {
	_type = EntityType::EXPLOSION;
	_explosionType = explosionType;
	_explosionList = {
		{ExplosionType::EDEFAULT, Vector2(66, 68)},
		{ExplosionType::EPLAYER, Vector2(119, 67)},
	};
	setSize(_explosionList[explosionType]);
}

/**
 * @brief Update Funktion der Explosion
 * @details Wird bei jeder Iteration der Gameloop
 * 			aufgerufen.
 * 
 * @see Controller
 */
void Explosion::update() {
	
}

/**
 * @brief Kollisionsevent der Explosion
 * @details Explosionen haben keine Kollisionen
 * 
 * @see Controller
 * 
 * @param collisionPartner Kollisionspartner
 */
void Explosion::onCollision(std::shared_ptr<Object> collisionPartner) {
	
}

/**
 * @brief Gibt Identifikator der Explosion zurück
 * @details Entspricht dem Explosionstypen und
 * 			überschreibt die getIdentifier() von
 * 			Entity um den Explosionstypen als
 * 			Identifikator zu nutzen.
 * 			So kann die View die Textur verschiedener
 * 			Explosionstypen einlesen.
 * 
 * @return int 
 */
int Explosion::getIdentifier() {
	return _explosionType;
}

/**
 * @brief Gibt den Explosionstyp zurück
 * 
 * @return ExplosionType Explosionstyp
 */
ExplosionType Explosion::getExplosionType() {
	return _explosionType;
}