#include "levelmanager.h"

/**
 * @brief Erstellt Objekt der LevelManager Klasse
 * 
 * @param view Pointer auf View
 */
LevelManager::LevelManager(std::shared_ptr<View> view) {
	_view = view;
}

/**
 * @brief Lädt ein Level aus dem Dateisystem und erstellt ein Levelobjekt
 * @details Liest die Leveldatei Byte für Byte aus und speichert
 * 			Breite, Höhe, Bewegungsgeschwindigkeit, Pixeldaten und
 * 			Entites.
 * 			Lässt die Leveltextur von der View buffern.
 * 			Erstellt auch ein Spielerobjekt.
 * 
 * @see https://docs.google.com/spreadsheets/d/1P4jnQqbnV6f9iMamDetU1nkwRxaJxuRgE43Ap-PSlX0
 * 
 * @param levelName Name des Levels
 * @return Levelobjekt
 */
std::shared_ptr<Level> LevelManager::load(std::string levelName) {
	std::string path = "./levels/" + levelName + ".sc";
	
	std::ifstream file;
	file.open(path, std::ios::out | std::ios::binary);
	
	char headerBuffer[LEVEL_HEADER_SIZE];
	file.read(headerBuffer, LEVEL_HEADER_SIZE);
	
	int width = byte_to_int16(headerBuffer, 2);
	int height = byte_to_int16(headerBuffer, 6);
	int scrollSpeed = byte_to_int16(headerBuffer, 10);
	int entityCount = byte_to_int16(headerBuffer, 14);
	
	auto player = std::make_shared<Player>();
	_view->buffer(player);
	_view->startAnimation(player);
	
	auto entityList = std::vector<std::shared_ptr<Entity>>();
	entityList.push_back(player);
	
	for(int i = 0; i < entityCount; i++) {
		char entityBuffer[LEVEL_ENTITY_SIZE];
		file.read(entityBuffer, LEVEL_ENTITY_SIZE);
		
		int type = byte_to_int16(entityBuffer, 0);
		int x = byte_to_int16(entityBuffer, 4);
		int y = byte_to_int16(entityBuffer, 8);
		
		std::shared_ptr<Entity> entity;

		switch(type) {
			default:
			case 1:
				entity = std::make_shared<Rocket>();
				break;
			case 2:
				entity = std::make_shared<Fuel>();
				break;
			case 3:
				entity = std::make_shared<Building>();
				break;
		}

		entity->setPosition(Vector2(x, y));
		entity->setVelocity(entity->getVelocity().add(-scrollSpeed, 0));
		_view->buffer(entity);
		
		std::cout << "[LevelManager] loaded entity: type#" << type << " x#" << x << " y#" << y << std::endl;
		
		entityList.push_back(entity);
	}
		
	// Speicher wird von der Texturenklasse
	// automatisch wieder freigegeben.
	uint pixelDataSize = width * height * 4;
	char* pixelData = (char*)malloc(pixelDataSize);
	file.read(pixelData, pixelDataSize);
	
	int i = 0;
	auto collisionMap = new int[width * height];
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			collisionMap[y * width + x] = byte_to_uint8(pixelData, i * 4 + 3);
			i++;
		}
	}
	
	auto texture = std::make_shared<Texture>(pixelData, width, height);
	auto level = std::make_shared<Level>(levelName, width, height, scrollSpeed, player, entityList, collisionMap);
	_view->buffer(level, texture);
	
	return level;
}