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


/*******************************************************************
 * Sprite movement
 *******************************************************************/

// Move the sprite if possible. Takes a Room reference to check for collisions and room boundaries.
// TODO move this into a separate PlayerEntity class
bool SpriteEntity::moveBy(int dx, int dy, Room& room) {
	// Calculate new position
	int newX = roomX + dx;
	int newY = roomY + dy;

	// Check room boundaries
	if (newX < 0 || newX >= room.getWidth() || newY < 0 || newY >= room.getHeight()) {
		// New position is out of boundaries, movement not allowed
		return false;
	}

	// Check sprite collisions
	// TODO

	// Set new position
	setPosition(newX, newY);

	// Movement successful
	return true;
}

