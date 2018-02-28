#ifndef SPRITEENTITY_HPP_
#define SPRITEENTITY_HPP_

#include <string>
#include <SFML/Graphics.hpp>

#include "Room.hpp"

class SpriteEntity {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	SpriteEntity();
	SpriteEntity(std::string roomName_, int x, int y);

	// Forbid copy, but allow move operations
	SpriteEntity(const SpriteEntity& other)            = delete;  // copy constructor
	SpriteEntity& operator=(const SpriteEntity& other) = delete;  // copy assignment
	SpriteEntity(SpriteEntity&& other)                 = default;  // move constructor
	SpriteEntity& operator=(SpriteEntity&& other)      = default;  // move assignment


	/*******************************************************************
	 * Getters and setters
	 *******************************************************************/
	// Get reference to Sprite of entity.
	sf::Sprite& getSprite();

	// Get position in room
	int getX();
	int getY();

	// Set position in room (will update the Sprite's position)
	void setPosition(int newX, int newY);


	/*******************************************************************
	 * Sprite movement
	 *******************************************************************/
	// Move the sprite if possible. Takes a Room reference to check for collisions and
	// room boundaries. Returns true if movement was successful.
	// TODO move this into a separate PlayerEntity class
	bool moveBy(int dx, int dy, Room& room);


	/*******************************************************************
	 * Data
	 *******************************************************************/
	// Entity room location
	std::string roomName;

	// Tile grid size
	int GRID_SIZE = 32;

private:
	// Sprite
	sf::Sprite sprite;

	// Entity location
	int roomX;
	int roomY;
};


/*******************************************************************
 * Inline methods
 *******************************************************************/

// Get reference to Sprite of entity.
inline sf::Sprite& SpriteEntity::getSprite() {
	return sprite;
}

// Get X coordinate of entity position in room.
inline int SpriteEntity::getX() {
	return roomX;
}

// Get Y coordinate of entity position in room.
inline int SpriteEntity::getY() {
	return roomY;
}

#endif /* SPRITEENTITY_HPP_ */
