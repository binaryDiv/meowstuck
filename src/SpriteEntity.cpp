#include "SpriteEntity.hpp"


/*******************************************************************
 * Construction and destruction
 *******************************************************************/

// Default constructor
SpriteEntity::SpriteEntity() {
}

// Actual constructor
SpriteEntity::SpriteEntity(std::string roomName_, int x, int y) :
	roomName {roomName_}
{
	// Set position, which will also update the Sprite position
	setPosition(x, y);
}


/*******************************************************************
 * Getters and setters
 *******************************************************************/

// Set position in room (will update the Sprite's position)
void SpriteEntity::setPosition(int newX, int newY) {
	// Set position variables
	roomX = newX;
	roomY = newY;

	// Update Sprite position
	sprite.setPosition(GRID_SIZE * roomX, GRID_SIZE * roomY);
}

