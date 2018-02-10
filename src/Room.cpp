#include "Room.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


/*******************************************************************
 * Construction and destruction
 *******************************************************************/

Room::Room() {
}

Room::Room(const std::string& name, int width, int height) {
	this->name = name;
	this->width = width;
	this->height = height;
}


/*******************************************************************
 * Loading
 *******************************************************************/

// Parse tile data from a JSON array of strings and create sprite field
void Room::loadTileData(json& tileData) {
	// Parse each row
	for (auto& rowData : tileData) {
		std::string rowStr = rowData;
		std::cout << "Tile row: " << rowStr << "\n";

		// TODO actually parse data and create Sprites
	}
}

