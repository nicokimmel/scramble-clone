#include "eventmanager.h"

EventManager::EventManager() {
	_ticks = 0;
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
void EventManager::registerEvent(std::string identifier, EventType eventType, eventCallback callback) {
	_eventMap[eventType][identifier] = callback;
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

void EventManager::registerUpdate(std::string identifier, uint ticks, updateCallback callback) {
	_updateMap[ticks][identifier] = callback;
}

void EventManager::unregisterEvent(std::string identifier) {
	
}

void EventManager::tick() {
	for(auto const& outer : _updateMap) {
		uint ticks = outer.first;
		if(_ticks % ticks == 0) {
			for(auto const& inner : outer.second) {
				std::string identifier = inner.first;
				updateCallback callback = inner.second;
				
				std::invoke(callback);
			}
		}
	}
	
	_ticks++;
}