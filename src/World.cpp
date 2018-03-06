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

		// Parse player data
		{
			// Get player data
			auto& playerData = worldData["player"];

			// Debug output
			std::cout << "Initializing player: position (" << playerData["startx"] << ","
			          << playerData["starty"] << "), sprite: " << playerData["sprite"] << "\n";

			// Create player entity
			playerEntity = SpriteEntity (playerData["startroom"], playerData["startx"], playerData["starty"]);

			// Get tileset and tile index (simple JSON array)
			Tileset& playerTileset = getTileset(playerData["sprite"][0]);
			int playerTileIndex = playerData["sprite"][1];

			// Set player sprite (JSON: array with tileset name and tile index)
			playerTileset.setSpriteToTile(playerEntity.getSprite(), playerTileIndex);
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
	// Check if key already exists
	if (tilesets.count(tilesetName) > 0) {
		throw std::runtime_error("Tileset '" + tilesetName + "' already exists in map");
	}

	// Create new Tileset object and insert it into tilesets map
	tilesets[tilesetName] = Tileset {};

	// Load tileset texture
	tilesets[tilesetName].loadTilesetFromFile("res/" + tilesetName);

	// Return reference to tileset
	return tilesets[tilesetName];
}

// Gets a tileset by name (throws exception if tileset does not exist)
Tileset& World::getTileset(const std::string& tilesetName) {
	// Check if tileset exists (std::map::at will throw an exception otherwise)
	try {
		// Return reference to tileset
		return tilesets.at(tilesetName);
	}
	catch (std::out_of_range& e) {
		throw std::runtime_error("Tileset '" + tilesetName + "' not found in map of tilesets");
	}
}

// Adds and loads a room (throws exception if room already exists)
Room& World::loadRoom(const std::string& roomName, json& roomData) {
	// Check if key already exists
	if (rooms.count(roomName) > 0) {
		throw std::runtime_error("A room called '" + roomName + "' already exists in map");
	}

	// Create new Room object and insert it into rooms map
	rooms[roomName] = Room (roomName, roomData["width"], roomData["height"]);

	// Shortcut reference
	Room& room = rooms[roomName];

	// Set room's tileset
	Tileset& tileset = getTileset(roomData["tileset"]);
	room.setTileset(&tileset);

	// Parse tile data to sprites
	room.loadTileData(roomData["tiledata"]);

	// Parse teleports
	for (auto& teleportItem : roomData["teleports"]) {
		// Get from and destination coordinates
		CoordXY fromXY {teleportItem[0], teleportItem[1]};
		CoordRoomXY destRXY {teleportItem[2], teleportItem[3], teleportItem[4]};

		std::cout << "Adding teleport from " << fromXY.first << "," << fromXY.second << " to room "
			<< destRXY.room << " " << destRXY.x << "," << destRXY.y << std::endl;

		// Add teleport to room
		room.addTeleport(fromXY, destRXY);
	}

	// Return reference to room
	return room;
}

// Gets a room by name (throws exception if room does not exist)
Room& World::getRoom(const std::string& roomName) {
	// Check if room exists (std::map::at will throw an exception otherwise)
	try {
		// Return reference to room
		return rooms.at(roomName);
	}
	catch (std::out_of_range& e) {
		throw std::runtime_error("Room '" + roomName + "' does not exist");
	}
}

