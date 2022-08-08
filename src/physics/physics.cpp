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
                std::cout << "Colission Entity" << std::endl;
			}
		}
        if(checkCollision_World(entity1.get(), currentLevel.get())) {
            entity1->onCollision(nullptr);
			std::cout << "Colission World" << std::endl;
        }
	}
}

void Physics::checkCollision(std::vector<std::shared_ptr<Object>> playerRelatedEntitys, std::vector<std::shared_ptr<Object>> nonPlayerRelatedEntites, std::shared_ptr<World> currentLevel) {
	for(auto entity1 : playerRelatedEntitys) {
		for(auto entity2 : nonPlayerRelatedEntites) {
			if(checkCollision_Objects(entity1.get(), entity2.get())) {
			 	entity1->onCollision(entity2);
				entity2->onCollision(entity1);
				std::cout << "Colission Entity" << std::endl;
			}
		}
		if(checkCollision_World(entity1.get(), currentLevel.get())) {
			entity1->onCollision(nullptr);
			std::cout << "Colission World" << std::endl;
		}
	}
}

bool Physics::checkCollision_Objects(Object *a, Object *b) {
    a->setMax(Vector2(a->getPosition().getX() + a->getSize().getX(), a->getPosition().getY() + a->getSize().getY()));
	a->setMin(Vector2(a->getPosition().getX(), a->getPosition().getY()));
    b->setMax(Vector2(b->getPosition().getX() + b->getSize().getX(), b->getPosition().getY() + b->getSize().getY()));
	b->setMin(Vector2(b->getPosition().getX(), b->getPosition().getY()));

    if(a->getMax().getX() < b->getMin().getX() or a->getMin().getX() > b->getMax().getX()) return false;
    if(a->getMax().getY() < b->getMin().getY() or a->getMin().getY() > b->getMax().getY()) return false;

    return true;
}

bool Physics::checkCollision_World(Object *a, World *b) {
    a->setMax(Vector2(a->getPosition().getX() + a->getSize().getX(), a->getPosition().getY() + a->getSize().getY()));
	a->setMin(Vector2(a->getPosition().getX(), a->getPosition().getY()));

    if(b->getAlpha(a->getMin().getX(), a->getMin().getY()) == 255) return true;
    if(b->getAlpha(a->getMin().getX(), a->getMax().getY()) == 255) return true;
    if(b->getAlpha(a->getMax().getX(), a->getMin().getY()) == 255) return true;
    if(b->getAlpha(a->getMax().getX(), a->getMax().getY()) == 255) return true;
    
    return false;
}

void Physics::move(Object *a) {
    auto posX = a->getPosition().getX() + a->getVelocity().getX();
    auto posY = a->getPosition().getY() + a->getVelocity().getY();
    a->setPosition(Vector2(posX, posY));
}

void Physics::move(Object *a, int vx, int vy) {
    auto posX = a->getPosition().getX() + a->getVelocity().getX() + vx;
    auto posY = a->getPosition().getY() + a->getVelocity().getY() + vy;
    a->setPosition(Vector2(posX, posY));
}
