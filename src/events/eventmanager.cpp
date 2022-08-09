#include "eventmanager.h"

EventManager::EventManager() {
	_ticks = 0;
	_callLaterId = 0;
}

/**
 * @brief Registriert Callback der beim Eventaufruf ausgeführt wird 
 * @details Speichert Identifier und Callback in einer Map um bei einem
 * 			Aufruf des Events die entsprechende Funktion ausführen zu
 * 			können.
 * 
 * @todo Pointer Adresse des Callbacks als Identifier nutzen.
 * 
 * @param identifier Identifikator
 * @param eventType Eventtyp
 * @param eventCallback Callback
 */
void EventManager::registerEvent(std::string identifier, EventType eventType, eventCallback func) {
	_eventMap[eventType][identifier] = func;
}

/**
 * @brief Entfernt Callback aus Map
 * 
 * @param identifier Identifikator
 * @param eventType Eventtyp
 */
void EventManager::unregisterEvent(std::string identifier, EventType eventType) {
	_eventMap[eventType].erase(identifier);
}

/**
 * @brief Führt alle Callbackfunktionen eines Eventtypen aus
 * 
 * @param eventType Eventtyp
 * @param data Eventinformationen
 */
void EventManager::fireEvent(const EventType eventType, std::shared_ptr<EventData> data) {
	for(auto const& entry : _eventMap[eventType]) {
		std::invoke(entry.second, data);
	}
}

void EventManager::registerUpdate(std::string identifier, uint ms, callback func) {
	UpdateInformation ui;
	ui.ms = ms;
	ui.func = func;
	ui.first = true;
	ui.remove = false;
	_updateMap[identifier] = ui;
}

void EventManager::unregisterUpdate(std::string identifier) {
	_updateMap[identifier].remove = true;
}

void EventManager::callLater(uint ms, callback func) {
	std::string identifier = "callLater" + _callLaterId;
	_callLaterId++;
	
	registerUpdate(identifier, ms, [this, identifier, func]() {
		std::cout << identifier << std::endl;
		unregisterUpdate(identifier);
		std::invoke(func);
		return true;
	});
}

void EventManager::tick() {
	auto it = _updateMap.begin();
	while(it != _updateMap.end()) {
		UpdateInformation& info = it->second;
		if(_ticks % (info.ms * 60/1000) == 0) {
			if(!info.first) {
				std::invoke(info.func);
			}
			info.first = false;
		}
		if(info.remove) {
			std::cout << "REMOVE " << it->first << std::endl;
			it = _updateMap.erase(it);
		} else {
			++it;
		}
	}
	
	_ticks++;
}