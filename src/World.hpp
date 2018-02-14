#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <string>
#include <map>

#include "Room.hpp"

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
	 * Loading, Resource Management
	 *******************************************************************/
	// Load world data from JSON file
	void loadFromFile(const std::string& filename);


	/*******************************************************************
	 * World meta data
	 *******************************************************************/
	// World title
	std::string title;


	/*******************************************************************
	 * World content
	 *******************************************************************/
	// List of rooms
	std::map<std::string, Room> rooms;
};

#endif /* WORLD_HPP_ */
