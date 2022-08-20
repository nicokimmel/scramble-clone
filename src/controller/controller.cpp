#include "controller.h"

/**
 * @brief Erstellt Objekt von Controller
 * @details Erstellt Objekte von EventManager und LevelManager.
 *			Lädt das erste Level.
 * 
 * @param view Objekt der Viewklasse
 */
Controller::Controller(std::shared_ptr<View> view) {
	_view = view;
	_frozen = false;
	_physics = std::make_shared<Physics>();
	_eventManager = std::make_shared<EventManager>();
	_levelManager = std::make_shared<LevelManager>(view);
	_currentLevel = _levelManager->load("stageonesmallpink");
}

/**
 * @brief Initialisiert den Controller
 * @details Registriert Callbacks für Fenstereingaben und
 * 			Zeitgeber für Animationen und Spielertreibstoff.
 */
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
	
	_eventManager->registerUpdate("viewTextureUpdate", 100, [this]() {
		_view->animate();
	});
	
	_eventManager->registerUpdate("viewSkyTextureUpdate", 800, [this]() {
		_view->animate(_currentLevel->getSky());
	});
}

/**
 * @brief Startet und steuert GameLoop
 * @details Führt 60 mal pro Sekunde die update Funktionen
 * 			aller Entitäten aus.
 * 			Lässt Entitäten durch die View zeichnen.
 * 			Lässt Kolission durch Phsyiscs überprüfen.
 * 			Tastet auch den Input ab.
 */
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

				_physics->checkCollision(_currentLevel);
				checkPlayer();
				checkRockets();
				checkWindowBounds();
			}
			
			_eventManager->tick();

			tDelta--;
			
			_ups++;
			_ticks++;
		}
		
		_view->clear();
		for(auto entity : _currentLevel->getEntityList()) {
			_view->render(entity);
		}
		_view->render(_currentLevel);
		_view->flip();
		_fps++;
		
		debug();
		
		if(!_view->isWindowOpen()) {
			stop();
		}
	}
}

/**
 * @brief Aktualisiert sekündlich Debuganzeigen im Titel
 */
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

/**
 * @brief Stoppt den Controller
 * @details Stoppt die Gameloop und schließt das Fenster.
 */
void Controller::stop() {
	_running = false;
	glfwTerminate();
}

/**
 * @brief Überprüft Eingaben des Spielers
 * @details Liest den Status der Tasten aus einer Hilfstabelle
 */
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

/**
 * @brief Überprüft ob Spieler abgestürtzt und stoppt Spiel falls Leben auf 0
 */
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

/**
 * @brief Überprüft Raketen und startet sie, falls in Reichweite
 */
void Controller::checkRockets() {
    for(auto entity : _currentLevel->getEntityList()) {
        if(entity->getType() == EntityType::ROCKET) {
            auto rocket = std::static_pointer_cast<Rocket>(entity);
            auto player = _currentLevel->getPlayer();
            if(player->getPosition().getX() + player->getSize().getX() >= entity->getPosition().getX() - 100) {
                rocket->launch();
                _view->startAnimation(rocket);
            }
        }
    }
}

/**
 * @brief Überprüft ob Entitäten außerhalb des Fensters sind und entfernt sie.
 */
void Controller::checkWindowBounds() {
	for(auto entity : _currentLevel->getEntityList()) {
        if(entity->getType() == EntityType::ROCKET) {
			if(entity->getPosition().getY() > WINDOW_HEIGHT || entity->getPosition().getX() + entity->getSize().getX() < 0) {
				_currentLevel->despawn(entity);
			}
        }
		if(entity->getType() == EntityType::LASER) {
			if(entity->getPosition().getX() > WINDOW_WIDTH) {
				_currentLevel->despawn(entity);
			}
        }
		if(entity->getType() == EntityType::EXPLOSION) {
			if(entity->getPosition().getY() > WINDOW_HEIGHT || entity->getPosition().getX() + entity->getSize().getX() < 0) {
				_currentLevel->despawn(entity);
			}
        }
    }
}