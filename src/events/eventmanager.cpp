#include "eventmanager.h"

/**
 * @brief Erstellt Objekt des EventManagers
 */
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
 * @param identifier Identifikator
 * @param eventType Eventtyp
 * @param eventCallback Callback
 */
void EventManager::registerEvent(std::string identifier, EventType eventType, eventCallback func) {
	_eventMap[eventType][identifier] = func;
}

/**
 * @brief Entfernt Callback aus Eventliste
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

/**
 * @brief Führt übergebenen Callback in gegebenem Intervall aus
 * 
 * @param identifier Identifikator
 * @param ms Intervall in ms
 * @param func Callbackfunktion
 */
void EventManager::registerUpdate(std::string identifier, uint ms, callback func) {
	_updateMap[identifier] = UpdateInformation(ms, func, true, false);
}

/**
 * @brief Löscht Callback aus Updateliste
 * 
 * @param identifier Identifikator
 */
void EventManager::unregisterUpdate(std::string identifier) {
	_updateMap[identifier].remove = true;
}

/**
 * @brief Führt Callback mit einer Verzögerung aus
 * @details Nutzt EventManager::registerUpdate() um den Callback
 * 			einmalig auszuführen und ihn danach direkt zu löschen.
 * 
 * @param ms Verzögerung in ms
 * @param func Callbackfunktion
 */
void EventManager::callLater(uint ms, callback func) {
	std::string identifier = "callLater" + std::to_string(_callLaterId);
	_callLaterId++;
	
	registerUpdate(identifier, ms, [this, identifier, func]() {
		unregisterUpdate(identifier);
		std::invoke(func);
	});
}

/**
 * @brief Erhöht die Tickvariable des EventManagers
 * @details Wird genutzt um eine Taktfrequenz abzuleiten.
 * 			Erwartet eine Tickrate von 60/Sekunde.
 */
void EventManager::tick() {
	auto it = _updateMap.begin();
	while(it != _updateMap.end()) {
		UpdateInformation& info = it->second;
		if(_ticks % (info.ms * 60/1000) == 0) {
			if(!info.first) {
				std::invoke(info.func);
			}
			info.first = false;
			
			if(info.remove) {
				it = _updateMap.erase(it);
				continue;
			}
		}
		++it;
	}
	
	_ticks++;
}