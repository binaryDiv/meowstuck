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
 * Loading, Resource Management
 *******************************************************************/

// Load world data from JSON file
void World::loadFromFile(const std::string& filename) {
	// TODO Better error handling (let this function throw Exceptions and handle them in main() maybe?)

	// Open file stream
	std::ifstream ifs (filename);

	if (!ifs) {
		std::cerr << "[World::loadFromFile] ERROR: could not open file '" << filename << "'" << std::endl;
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

		// Parse rooms
		for (auto& roomItem : worldData["rooms"].items()) {
			// Get room name and room data
			std::string roomName = roomItem.key();
			json roomData = roomItem.value();

			// XXX Debug output
			std::cout << "\nCreating room '" << roomName << "' of size " << roomData["width"]
			          << "x" << roomData["height"] << "\n";

			// Create new Room object and fill it with room data
			Room newRoom (roomName, roomData["width"], roomData["height"]);

			// TODO Set tileset
			// newRoom.setTileset( ... get tileset ...);

			// Parse tile data to sprites
			newRoom.loadTileData(roomData["tiledata"]);

			// Insert new room into room map
			rooms[roomName] = std::move(newRoom);
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

