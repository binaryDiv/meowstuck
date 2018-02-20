#include "World.hpp"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


/*******************************************************************
 * Construction and destruction
 *******************************************************************/

World::World() {
}


/*******************************************************************
 * Loading, resource management
 *******************************************************************/

// Load world data from JSON file
void World::loadFromFile(const std::string& filename) {
	// TODO Better error handling (let this function throw Exceptions and handle them in main() maybe?)

	// Open file stream
	std::ifstream ifs (filename);

	if (!ifs) {
		std::cerr << "[World::loadFromFile] ERROR: could not open file '" << filename << "'" << std::endl;
		// TODO throw exception
		return;
	}

	try {
		// Read JSON data
		json worldData;
		ifs >> worldData;

		// Parse meta data
		this->title = worldData.value("title", "Unnamed");
		
		// XXX Debug output
		std::cout << "Loading world '" << this->title << "' with "
		          << worldData["rooms"].size() << " rooms\n";

		// Load tilesets
		for (auto& tilesetItem : worldData["tilesets"]) {
			// Get tileset name as string
			std::string tilesetName = tilesetItem;

			// Debug output
			std::cout << "Loading tileset '" << tilesetName << "'\n";

			// Load and add tileset
			loadTileset(tilesetName);
		}

		// Parse rooms
		for (auto& roomItem : worldData["rooms"].items()) {
			// Get room name and room data
			std::string roomName = roomItem.key();
			json roomData = roomItem.value();

			// Debug output
			std::cout << "Creating room '" << roomName << "' of size " << roomData["width"]
			          << "x" << roomData["height"] << "\n";

			// Create, load and add new room
			loadRoom(roomName, roomData);
		}
	}
	catch (json::parse_error& e) {
		std::cerr << "[World::loadFromFile] ERROR: " << e.what() << std::endl;
		return;
	}
	catch (json::type_error& e) {
		std::cerr << "[World::loadFromFile] ERROR: " << e.what() << std::endl;
		return;
	}
}

// Adds and loads a tileset (throws exception if tileset already exists)
Tileset& World::loadTileset(const std::string& tilesetName) {
	// TODO check if already exists -> exception

	// Create new Tileset object and insert it into tilesets map
	tilesets[tilesetName] = Tileset {};

	// Load tileset texture
	tilesets[tilesetName].loadTilesetFromFile("res/" + tilesetName);

	// Return reference to tileset
	return tilesets[tilesetName];
}

// Gets a tileset by name (throws exception if tileset does not exist)
Tileset& World::getTileset(const std::string& tilesetName) {
	// TODO check if exists

	// Return reference to tileset
	return tilesets[tilesetName];
}

// Adds and loads a room (throws exception if room already exists)
Room& World::loadRoom(const std::string& roomName, json& roomData) {
	// TODO check if already exists -> exception

	// Create new Room object and insert it into rooms map
	rooms[roomName] = Room (roomName, roomData["width"], roomData["height"]);

	// Shortcut reference
	Room& room = rooms[roomName];

	// Set room's tileset
	Tileset& tileset = getTileset(roomData["tileset"]);
	room.setTileset(&tileset);

	// Parse tile data to sprites
	room.loadTileData(roomData["tiledata"]);

	// Return reference to room
	return room;
}

// Gets a room by name (throws exception if room does not exist)
Room& World::getRoom(const std::string& roomName) {
	// TODO check if exists

	// Return reference to room
	return rooms[roomName];
}

