#ifndef SCRAMBLE_CONTROLLER_H
#define SCRAMBLE_CONTROLLER_H
#include <iostream>
#include "../utils/base.h"

#include <map>
#include <chrono>

#include "../events/eventmanager.h"
#include "../levels/levelmanager.h"
#include "../entities/player.h"
#include "../view/view.h"
#include "../physics/physics.h"
#include "../physics/object.h"

#include <algorithm>

class Player;

class Controller {
	private:
		std::shared_ptr<Physics> physics;
		bool _running;
		int _ticks, _fps, _ups;
		double _nextDebug;
		std::shared_ptr<View> _view;
		std::shared_ptr<EventManager> _eventManager;
		std::shared_ptr<LevelManager> _levelManager;
		std::shared_ptr<Level> _currentLevel;
		std::map<int, bool> _input;
		void onInput(std::shared_ptr<EventData>);
		void checkInput();
		void checkCollision();
		void checkPlayer();
		void checkRockets();
		void changeLevel();
		void debug();
	public:
		Controller(std::shared_ptr<View>);
		void init();
		void start();
		void stop();
};

#endif //SCRAMBLE_CONTROLLER_H