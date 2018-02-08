#ifndef WORLD_H_
#define WORLD_H_

#include <string>

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

private:
};

#endif /* WORLD_H_ */
