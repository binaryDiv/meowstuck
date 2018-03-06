#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <string>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include "SpriteMatrix.hpp"
#include "Tileset.hpp"
#include "CoordUtils.hpp"

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

	// Set tileset (as a pointer)
	void setTileset(Tileset* tileset);

	// Set tile at a specific position to a tile referenced by its ID
	void setTile(int x, int y, int tileID);

	// Adds a teleport (room coordinates -> destination room + coordinates).
	// Overwrites existing teleports at the same position.
	void addTeleport(CoordXY fromXY, CoordRoomXY toRoomXY);


	/*******************************************************************
	 * Collision detection and events
	 *******************************************************************/
	// Check if position is walkable
	bool isTileWalkable(int x, int y);

	// Checks for teleport at specific position
	bool hasTeleportAt(int x, int y);

	// Gets teleport destination
	CoordRoomXY getTeleportDestinationFrom(int x, int y);


	/*******************************************************************
	 * Room meta data
	 *******************************************************************/
	// Room name/ID
	std::string name;

	// Room size
	int getWidth();
	int getHeight();

private:
	// Pointer to tileset
	Tileset* roomTileset = nullptr;


	/*******************************************************************
	 * Room content
	 *******************************************************************/
public:
	// Tiles: field of sprites
	SpriteMatrix tileField;

	// Teleports map: (fromX, fromY) -> (toRoom, toX, toY)
	std::map<CoordXY, CoordRoomXY> teleports;
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
