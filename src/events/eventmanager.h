#ifndef SCRAMBLE_EVENTMANAGER_H
#define SCRAMBLE_EVENTMANAGER_H

#include "../utils/base.h"

#include <map>
#include <vector>
#include <functional>

#include "eventdata.h"

/**
 * @brief Liste aller Eventtypen
 */
enum EventType {
	INPUT, COLLISION
};

typedef std::function<void(std::shared_ptr<EventData>)> callback;

/**
 * @brief Verwaltet Ereignisse und ruft passende Callback Funktionen auf
 */
class EventManager {
	private:
		std::map<EventType, std::map<std::string, callback>> _callbackMap;
	public:
		void registerEvent(std::string, EventType, callback);
		void unregisterEvent(std::string, EventType);
		void fireEvent(const EventType, std::shared_ptr<EventData>);
};

#endif //SCRAMBLE_EVENTMANAGER_H