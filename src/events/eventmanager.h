#ifndef SCRAMBLE_EVENTMANAGER_H
#define SCRAMBLE_EVENTMANAGER_H

#include "../utils/base.h"

#include <map>
#include <vector>
#include <functional>

#include "eventdata.h"

typedef std::function<void(std::shared_ptr<EventData>)> eventCallback;
typedef std::function<void()> callback;

/**
 * @brief Liste aller Eventtypen
 */
enum EventType {
	INPUT, COLLISION
};

struct UpdateInformation {
	uint ms;
	callback func;
	bool first;
	bool remove;
};

/**
 * @brief Verwaltet Ereignisse und ruft passende Callback Funktionen auf
 * @details Dient auch als Taktgeber
 */
class EventManager {
	private:
		uint _ticks;
		uint _callLaterId;
		std::map<EventType, std::map<std::string, eventCallback>> _eventMap;
		std::map<std::string, UpdateInformation> _updateMap;
	public:
		EventManager();
		void registerEvent(std::string, EventType, eventCallback);
		void unregisterEvent(std::string, EventType);
		void fireEvent(const EventType, std::shared_ptr<EventData>);
		void registerUpdate(std::string, uint, callback);
		void unregisterUpdate(std::string);
		void callLater(uint, callback);
		void tick();
};

#endif //SCRAMBLE_EVENTMANAGER_H