#ifndef SCRAMBLE_CONTROLLER_H
#define SCRAMBLE_CONTROLLER_H

#include "../utils/base.h"

#include <map>
#include <chrono>

#include "../events/eventmanager.h"
#include "../levels/levelmanager.h"
#include "../entities/player.h"
#include "../view/view.h"

class Player;

class Controller {
	private:
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
		void checkPlayerState();
		void checkCollision();
		void changeLevel();
		void debug();
	public:
		Controller(std::shared_ptr<View>);
		void init();
		void start();
		void stop();
};

#endif //SCRAMBLE_CONTROLLER_H