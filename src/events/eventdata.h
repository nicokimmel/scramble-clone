#ifndef SCRAMBLE_EVENTDATA_H
#define SCRAMBLE_EVENTDATA_H

#include "../utils/base.h"

#include "../entities/entity.h"

/**
 * @brief Oberklasse der Eventinformationen
 */
class EventData {
	public:
		virtual ~EventData() = default;
};

/**
 * @brief Hält Informationen über Eingabeevent
 * @details Wrapper für den GLFW Input Callback
 * 			key: Keyboard key
 * 			scancode: Platform-specific keyboard key
 * 			action: GLFW_RELEASE | GLFW_PRESS | GLFW_REPEAT
 * 			mods: ALT, CTRL, SHIFT
 */
class InputEventData : public EventData {
	private:
		int _key;
		int _scancode;
		int _action;
		int _mods;
	public:
		InputEventData(int key, int scancode, int action, int mods) {
			_key = key;
			_scancode = scancode;
			_action = action;
			_mods = mods;
		}
		int getKey() { return _key; }
		int getScanCode() { return _scancode; }
		int getAction() { return _action; }
		int getMods() { return _mods; }
};

/**
 * @brief Hält Informationen über Kollisionsevent
 * @details Enthält beide Kollisionspartner in Form
 * 			von Entity Pointern.
 */
class CollisionEventData : public EventData {
	private:
		std::shared_ptr<Entity> _first;
		std::shared_ptr<Entity> _second;
	public:
		CollisionEventData(std::shared_ptr<Entity> first, std::shared_ptr<Entity> second) {
			_first = first;
			_second = second;
		}
		std::shared_ptr<Entity> getFirst() { return _first; }
		std::shared_ptr<Entity> getSecond() { return _second; }
};

#endif //SCRAMBLE_EVENTDATA_H