#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <string>
#include <nlohmann/json.hpp>

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

	// TODO Set tileset
	// void setTileset(Tileset& tileset);


	/*******************************************************************
	 * Room meta data
	 *******************************************************************/
	// Room name/ID
	std::string name;
	
	// Room size
	int width;
	int height;

	// Tileset name
	std::string tilesetName;


	/*******************************************************************
	 * Room content
	 *******************************************************************/
	// Sprite field
	// TODO
};

#endif /* ROOM_HPP_ */
