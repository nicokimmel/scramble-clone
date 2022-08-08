#include "controller.h"

Controller::Controller(std::shared_ptr<View> view) {
	_view = view;
	_eventManager = std::make_shared<EventManager>();
	_levelManager = std::make_shared<LevelManager>(view);
	_currentLevel = _levelManager->load("stageonesmall");
}

void Controller::init() {
	glfwSetWindowUserPointer(_view->getWindow(), this);
	glfwSetKeyCallback(_view->getWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto &self = *static_cast<Controller*>(glfwGetWindowUserPointer(window));
		if(action == GLFW_PRESS) {
			self._input[key] = true;
			if(key == GLFW_KEY_LEFT_CONTROL) {
				self._view->buffer(self._currentLevel->spawn());
			}
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
			int i = 0;
			for(auto entity : _currentLevel->getEntityList()) {
				entity->updateEntity();
				i++;
				if(entity->hasCrashed()) {
					_currentLevel->despawn(i);
				}
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
	
	if(player->hasCrashed()) {
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
	/*
	std::vector<std::shared_ptr<Object>> list = std::vector<std::shared_ptr<Object>>();
	for(auto entity : _currentLevel->getEntityList()) {
		list.push_back(entity);
	}
	physics->checkCollision2(list, _currentLevel);
	*/
	
	std::vector<std::shared_ptr<Object>> playerRelatedEntitys = std::vector<std::shared_ptr<Object>>();
	std::vector<std::shared_ptr<Object>> nonPlayerRelatedEntites = std::vector<std::shared_ptr<Object>>();

	for(auto entity : _currentLevel->getEntityList()) {
		if(entity->getType() != EntityType::PLAYER && entity->getType() != EntityType::MISSILE) {
			nonPlayerRelatedEntites.push_back(entity);
		} else {
			playerRelatedEntitys.push_back(entity);
		}
	}
	physics->checkCollision(playerRelatedEntitys, nonPlayerRelatedEntites, _currentLevel);
}