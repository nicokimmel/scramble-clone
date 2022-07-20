#include "eventmanager.h"

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
 * @param callback Callback
 */
void EventManager::registerEvent(std::string identifier, EventType eventType, callback callback) {
	_callbackMap[eventType][identifier] = callback;
}

/**
 * @brief Entfernt Callback aus Map
 * 
 * @param identifier Identifikator
 * @param eventType Eventtyp
 */
void EventManager::unregisterEvent(std::string identifier, EventType eventType) {
	_callbackMap[eventType].erase(identifier);
}

/**
 * @brief Führt alle Callbackfunktionen eines Eventtypen aus
 * 
 * @param eventType Eventtyp
 * @param data Eventinformationen
 */
void EventManager::fireEvent(const EventType eventType, std::shared_ptr<EventData> data) {
	for(auto const& entry : _callbackMap[eventType]) {
		std::invoke(entry.second, data);
	}
}