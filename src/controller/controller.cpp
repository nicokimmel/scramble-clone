#include "controller.h"

Controller::Controller(std::shared_ptr<View> view) {
	_view = view;
	_eventManager = std::make_shared<EventManager>();
	_levelManager = std::make_shared<LevelManager>(view);
	_currentLevel = _levelManager->load("stageone");
}

void Controller::init() {
	glfwSetWindowUserPointer(_view->getWindow(), this);
	glfwSetKeyCallback(_view->getWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto &self = *static_cast<Controller*>(glfwGetWindowUserPointer(window));
		if(action == GLFW_PRESS) {
			self._input[key] = true;
		} else if(action == GLFW_RELEASE) {
			self._input[key] = false;
		}
	});
}

void Controller::start() {
	_running = true;
	_ticks = 0, _fps = 0, _ups = 0;
	_nextDebug = glfwGetTime();
	
	double tLastUpdate = glfwGetTime();
	double tDelta = 0.0f;
	
	while(_running) {
		glfwPollEvents();
		
		double tNow = glfwGetTime();
		tDelta += (tNow - tLastUpdate) * TICKS_PER_SECOND;
		tLastUpdate = tNow;
		
		while(tDelta >= 1) {
			checkInput();
			_currentLevel->update();
			for(auto entity : _currentLevel->getEntityList()) {
				entity->updateEntity();
				physics->move(*entity.get());
			}
			checkCollision();
			checkPlayerState();
			
			tDelta--;
			
			_ups++;
			_ticks++;
		}
		
		_view->clear();
		_view->render(_currentLevel);
		for(auto entity : _currentLevel->getEntityList()) {
			_view->render(entity);
		}
		_view->flip();
		_fps++;
		
		debug();
		
		if(!_view->isWindowOpen()) {
			stop();
		}
	}
}

void Controller::debug() {
	double tNow = glfwGetTime();
	if(tNow >= _nextDebug) {
		std::stringstream windowTitle;
		windowTitle << "Scramble Clone (TICKS: " << _ticks << " FPS: " << _fps << " UPS: " << _ups << ")";
		glfwSetWindowTitle(_view->getWindow(), windowTitle.str().c_str());
		
		_fps = 0, _ups = 0;
		_nextDebug = tNow + 1;
	}
}

void Controller::stop() {
	_running = false;
	glfwTerminate();
}

void Controller::checkInput() {
	auto player = _currentLevel->getPlayer();
	if(_input[GLFW_KEY_UP]) {
		player->moveUp();
	}
	if(_input[GLFW_KEY_DOWN]) {
		player->moveDown();
	}
	if(_input[GLFW_KEY_LEFT]) {
		player->moveLeft();
	}
	if(_input[GLFW_KEY_RIGHT]) {
		player->moveRight();
	}
}

void Controller::checkPlayerState() {
	auto player = _currentLevel->getPlayer();
	int lives = player->getLives();
	
	if(player->hasFailed()) {
		std::string levelName = _currentLevel->getName();
		_currentLevel = _levelManager->load(levelName);
		_currentLevel->getPlayer()->setLives(lives);
		std::cout << "Player crashed, reset level" << std::endl << "Current lives: " << _currentLevel->getPlayer()->getLives() << std::endl;
	}
	
	if(player->getLives() <= 0) {
		//TODO: endscreen/main menu
		stop();
	}
}

void Controller::checkCollision() {
	auto player = _currentLevel->getPlayer();
	auto pos = player->getPosition();
	//int alpha = _currentLevel->getCollisionMap(pos.getX(), pos.getY());
	//if(alpha > 100) {
		//player->onCollision(nullptr);
		//return;
	//}
	
	auto checkedEntities = std::vector<std::shared_ptr<Entity>>();
	for(auto entity1 : _currentLevel->getEntityList()) {
		for(auto entity2 : _currentLevel->getEntityList()) {
			if(entity1 == entity2) {
				continue;
			}
			
			if(std::find(checkedEntities.begin(), checkedEntities.end(), entity1) != checkedEntities.end()) {
				continue;
			}
			checkedEntities.push_back(entity1);
			checkedEntities.push_back(entity2);

			entity1->setMax(Vector2(entity1->getPosition().getX() + entity1->getSize().getX(), entity1->getPosition().getY() + entity1->getSize().getY()));
			entity1->setMin(Vector2(entity1->getPosition().getX(), entity1->getPosition().getY()));
			entity2->setMax(Vector2(entity2->getPosition().getX() + entity2->getSize().getX(), entity2->getPosition().getY() + entity2->getSize().getY()));
			entity2->setMin(Vector2(entity2->getPosition().getX(), entity2->getPosition().getY()));

			//int entity1x = entity1->getPosition().getX() + entity1->getSize().getX();
			//int entity1y = entity1->getPosition().getY() + entity1->getSize().getY();
			
			//int entity2x = entity2->getPosition().getX() + entity2->getSize().getX();
			//int entity2y = entity2->getPosition().getY() + entity2->getSize().getY();
			
			if(physics->checkCollision_Objects(*entity1.get(), *entity2.get())) {
				
				entity1->onCollision(entity2);
				entity2->onCollision(entity1);
			}
		}
	}
}