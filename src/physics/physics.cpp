#include "physics.h"

/**
 * @brief Vergleicht Objekte
 * @details Iteriert über jedes Objekt um jedes mit jedem zu vergleichen ob eine Kollision vorliegt
 * 
 * @param currentLevel World Object damit auf Level Objeckte innerhalb des Level zugegriffen werden kann
 */
void Physics::checkCollision(std::shared_ptr<World> currentLevel) {
	auto checkedEntities = std::vector<std::shared_ptr<Object>>();
	auto list = currentLevel->getObjectList();

	bool inList = false;

    for(auto entity1 : list) {
		for(auto entity2 : list) {
			if(entity1 == entity2) {
				continue;
			}

			for(auto checked : checkedEntities) {
				if(checked == entity2) {
					inList == true;
					break;
				}
			}
			if(inList) {
				continue;
			}

			if(checkCollision_Objects(entity1, entity2)) {
				entity1->onCollision(entity2);
				entity2->onCollision(entity1);
			}
		}
        if(checkCollision_World(entity1, currentLevel)) {
            entity1->onCollision(nullptr);
        }
		checkedEntities.push_back(entity1);
	}
}

/**
 * @brief Checkt Collsion
 * @details Vergleicht zwei übergebene Objekte miteinander ob sie ineinander liegen anhand ihrer Eckpunkte
 * 
 * @param a Übergebenes Objekt a
 * @param b Übergebenes Objekt b
 * 
 * @return boolean ob Kollision vorhanden oder nicht
 */
bool Physics::checkCollision_Objects(std::shared_ptr<Object> a, std::shared_ptr<Object> b) {
	Vector2 maxA(a->getPosition().getX() + a->getSize().getX(), a->getPosition().getY() + a->getSize().getY());
	Vector2 minA(a->getPosition().getX(), a->getPosition().getY());
	
	Vector2 maxB(b->getPosition().getX() + b->getSize().getX(), b->getPosition().getY() + b->getSize().getY());
	Vector2 minB(b->getPosition().getX(), b->getPosition().getY());
	
    if(maxA.getX() < minB.getX() or minA.getX() > maxB.getX()) return false;
    if(maxA.getY() < minB.getY() or minA.getY() > maxB.getY()) return false;
	
    return true;
}

/**
 * @brief Checkt Collsion
 * @details Vergleicht ein übergebene Objekte und die Spielwelt ob sie ineinander liegen anhand der Alpha Kanäle
 * 
 * @param a Übergebenes Objekt a
 * @param b Übergebene Welt b
 * 
 * @return boolean ob Kollision vorhanden oder nicht
 */
bool Physics::checkCollision_World(std::shared_ptr<Object> a, std::shared_ptr<World> b) {
	Vector2 max(a->getPosition().getX() + a->getSize().getX(), a->getPosition().getY() + a->getSize().getY());
	Vector2 min(a->getPosition().getX(), a->getPosition().getY());

    if(b->getAlpha(min.getX(), min.getY()) == 255) return true;
    if(b->getAlpha(min.getX(), max.getY()) == 255) return true;
    if(b->getAlpha(max.getX(), min.getY()) == 255) return true;
    if(b->getAlpha(max.getX(), max.getY()) == 255) return true;
    
    return false;
}

/**
 * @brief Bewegt Objekt
 * @details Übergebenes Objekt wird anhand seiner Geschwindigkeit auf seine neue Possition gesetzt
 * 
 * @param a Übergebenes Objekt a
 * 
 */
void Physics::move(std::shared_ptr<Object> a) {
	auto pos = a->getPosition().add(a->getVelocity());
	a->setPosition(pos);
}

/**
 * @brief Bewegt Objekt
 * @details Übergebenes Objekt wird anhand einer übergebenen Geschwindigkeit auf seine neue Possition gesetzt
 * 
 * @param a Übergebenes Objekt a
 * 
 */
void Physics::move(std::shared_ptr<Object> a, int vx, int vy) {
	auto pos = a->getPosition().add(vx, vy);
    a->setPosition(pos);
}
