#include "physics.h"

void Physics::checkCollision2(std::vector<std::shared_ptr<Object>> entityList, std::shared_ptr<World> currentLevel) {
	auto checkedEntities = std::vector<std::shared_ptr<Object>>();
	
    for(auto entity1 : entityList) {
		for(auto entity2 : entityList) {
			if(entity1 == entity2) {
				continue;
			}
			
			if(std::find(checkedEntities.begin(), checkedEntities.end(), entity1) != checkedEntities.end()) {
				continue;
			}
			checkedEntities.push_back(entity1);
			checkedEntities.push_back(entity2);
			
			if(checkCollision_Objects(entity1.get(), entity2.get())) {
				entity1->onCollision(entity2);
				entity2->onCollision(entity1);
                //std::cout << "Colission Entity" << std::endl;
			}
		}
        if(checkCollision_World(entity1.get(), currentLevel.get())) {
            entity1->onCollision(nullptr);
			//std::cout << "Colission World" << std::endl;
        }
	}
}

void Physics::checkCollision(std::vector<std::shared_ptr<Object>> playerRelatedEntitys, std::vector<std::shared_ptr<Object>> nonPlayerRelatedEntites, std::shared_ptr<World> currentLevel) {
	for(auto entity1 : playerRelatedEntitys) {
		for(auto entity2 : nonPlayerRelatedEntites) {
			if(checkCollision_Objects(entity1.get(), entity2.get())) {
			 	entity1->onCollision(entity2);
				entity2->onCollision(entity1);
				//std::cout << "Colission Entity" << std::endl;
			}
		}
		if(checkCollision_World(entity1.get(), currentLevel.get())) {
			entity1->onCollision(nullptr);
			//std::cout << "Colission World" << std::endl;
		}
	}
}

bool Physics::checkCollision_Objects(Object *a, Object *b) {
	Vector2 maxA(a->getPosition().getX() + a->getSize().getX(), a->getPosition().getY() + a->getSize().getY());
	Vector2 minA(a->getPosition().getX(), a->getPosition().getY());
	
	Vector2 maxB(b->getPosition().getX() + b->getSize().getX(), b->getPosition().getY() + b->getSize().getY());
	Vector2 minB(b->getPosition().getX(), b->getPosition().getY());
	
    if(maxA.getX() < minB.getX() or minA.getX() > maxB.getX()) return false;
    if(maxA.getY() < minB.getY() or minA.getY() > maxB.getY()) return false;
	
    return true;
}

bool Physics::checkCollision_World(Object *a, World *b) {
	Vector2 max(a->getPosition().getX() + a->getSize().getX(), a->getPosition().getY() + a->getSize().getY());
	Vector2 min(a->getPosition().getX(), a->getPosition().getY());
	
    if(b->getAlpha(min.getX(), min.getY()) == 255) return true;
    if(b->getAlpha(min.getX(), max.getY()) == 255) return true;
    if(b->getAlpha(max.getX(), min.getY()) == 255) return true;
    if(b->getAlpha(max.getX(), max.getY()) == 255) return true;
    
    return false;
}

void Physics::move(Object *a) {
	auto pos = a->getPosition().add(a->getVelocity());
	a->setPosition(pos);
}

void Physics::move(Object *a, int vx, int vy) {
	auto pos = a->getPosition().add(vx, vy);
    a->setPosition(pos);
}
