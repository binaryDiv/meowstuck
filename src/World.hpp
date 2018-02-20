#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <string>
#include <map>

#include "Room.hpp"
#include "Tileset.hpp"

class World {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	World();

	// Forbid copy and move operations
	World(const World& other)            = delete;  // copy constructor
	World& operator=(const World& other) = delete;  // copy assignment
	World(World&& other)                 = delete;  // move constructor
	World& operator=(World&& other)      = delete;  // move assignment


	/*******************************************************************
	 * Loading, resource management
	 *******************************************************************/
	// Load world data from JSON file
	void loadFromFile(const std::string& filename);

	// Adds and loads a tileset (throws exception if tileset already exists)
	Tileset& loadTileset(const std::string& tilesetName);

	// Gets a tileset by name (throws exception if tileset does not exist)
	Tileset& getTileset(const std::string& tilesetName);

	// Adds and loads a room (throws exception if room already exists)
	Room& loadRoom(const std::string& roomName, json& roomData);

	// Gets a room by name (throws exception if room does not exist)
	Room& getRoom(const std::string& roomName);


	/*******************************************************************
	 * World meta data
	 *******************************************************************/
	// World title
	std::string title;


	/*******************************************************************
	 * World content
	 *******************************************************************/
private:
	// List of rooms
	std::map<std::string, Room> rooms;

	// List of tilesets
	std::map<std::string, Tileset> tilesets;
};

#endif /* WORLD_HPP_ */
