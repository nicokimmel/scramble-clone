#include "controller.h"

Controller::Controller(std::shared_ptr<View> view) {
	_view = view;
	_frozen = false;
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
				auto missile = self._currentLevel->spawn(EntityType::MISSILE);
				self._view->buffer(missile);
				self._view->startAnimation(missile);
			}
			if(key == GLFW_KEY_LEFT_ALT) {
				self._view->buffer(self._currentLevel->spawn(EntityType::LASER));
			}
		} else if(action == GLFW_RELEASE) {
			self._input[key] = false;
		}
	});
	
	_eventManager->registerUpdate("playerFuelUpdate", 500, [this]() {
		_currentLevel->getPlayer()->onFuel();
	});
	
	_eventManager->registerUpdate("viewTextureUpdate", 150, [this]() {
		_view->tick();
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
			
			if(!_frozen) {
				_currentLevel->update();
				
				for(auto entity : _currentLevel->getEntityList()) {
					entity->updateEntity();
					if(entity->hasCrashed()) {
						if(entity->getType() == EntityType::FUEL){
							_currentLevel->getPlayer()->addFuel(20);
						}
						if(entity->getType() == EntityType::LASER) {
							_currentLevel->despawn(entity);
						} else {
							auto explosion = _currentLevel->explode(entity);
							_view->buffer(explosion);
							_view->startAnimation(explosion);
							_eventManager->callLater(500, [this, explosion]() {
								_currentLevel->despawn(explosion);
							});
						}
					}
				}

				physics->checkCollision(_currentLevel);
				checkPlayer();
				checkRockets();
			}
			
			_eventManager->tick();

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

void Controller::checkPlayer() {
    auto player = _currentLevel->getPlayer();
    int lives = player->getLives();
    
    if(player->hasCrashed()) {
		_frozen = true;
		auto explosion = _currentLevel->explode(player);
		_view->buffer(explosion);
		_view->startAnimation(explosion);
		
		std::cout << "Player crashed, reset level in 1s. " << std::endl << "Current lives: " << _currentLevel->getPlayer()->getLives() << std::endl;
		_eventManager->callLater(1000, [this, lives]() {
			std::string levelName = _currentLevel->getName();
			_currentLevel = _levelManager->load(levelName);
			_currentLevel->getPlayer()->setLives(lives);
			_frozen = false;
		});
    }
    
    if(player->getLives() <= 0) {
        stop();
    }
}

void Controller::checkRockets() {
    for(auto entity : _currentLevel->getEntityList()) {
        if(entity->getType() == EntityType::ROCKET) {
            auto rocket = std::reinterpret_pointer_cast<Rocket>(entity);
            auto player = _currentLevel->getPlayer();
            if(player->getPosition().getX() + player->getSize().getX() >= entity->getPosition().getX() - 100) {
                rocket->launch();
                _view->startAnimation(rocket);
            }
        }
    }
}