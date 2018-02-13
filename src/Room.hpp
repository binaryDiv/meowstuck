#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <string>
#include <nlohmann/json.hpp>

#include "SpriteMatrix.hpp"

using json = nlohmann::json;

class Room {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	Room();
	Room(const std::string& name, int width, int height);

	// Forbid copy, but allow move operations
	Room(const Room& other)            = delete;  // copy constructor
	Room& operator=(const Room& other) = delete;  // copy assignment
	Room(Room&& other)                 = default;  // move constructor
	Room& operator=(Room&& other)      = default;  // move assignment


	/*******************************************************************
	 * Loading
	 *******************************************************************/
	// Parse tile data from a JSON array of strings and create sprite field
	void loadTileData(json& tileData);

	// Set tile at a specific position to a tile referenced by its ID
	void setTile(int x, int y, int tileID);

	// TODO Set tileset
	// void setTileset(Tileset& tileset);


	/*******************************************************************
	 * Room meta data
	 *******************************************************************/
	// Room name/ID
	std::string name;
	
	// Room size
	int getWidth();
	int getHeight();

	// Tileset name
	std::string tilesetName;


	/*******************************************************************
	 * Room content
	 *******************************************************************/
	// Tiles: field of sprites
	SpriteMatrix tileField;
};


/*******************************************************************
 * Inline methods
 *******************************************************************/

// Get room width, equal to tile field width
inline int Room::getWidth() {
	return tileField.width;
}

// Get room height, equal to tile field height
inline int Room::getHeight() {
	return tileField.height;
}

#endif /* ROOM_HPP_ */
