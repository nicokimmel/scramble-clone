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

typedef std::function<void(std::shared_ptr<EventData>)> eventCallback;
typedef std::function<void()> updateCallback;

/**
 * @brief Verwaltet Ereignisse und ruft passende Callback Funktionen auf
 */
class EventManager {
	private:
		uint _ticks;
		std::map<EventType, std::map<std::string, eventCallback>> _eventMap;
		std::map<uint, std::map<std::string, updateCallback>> _updateMap;
	public:
		EventManager();
		void registerEvent(std::string, EventType, eventCallback);
		void unregisterEvent(std::string, EventType);
		void fireEvent(const EventType, std::shared_ptr<EventData>);
		void registerUpdate(std::string, uint, updateCallback);
		void unregisterEvent(std::string);
		void tick();
};

#endif //SCRAMBLE_EVENTMANAGER_H