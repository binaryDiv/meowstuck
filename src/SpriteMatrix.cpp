#include "SpriteMatrix.hpp"

/*******************************************************************
 * Construction and destruction
 *******************************************************************/

// Default constructor
SpriteMatrix::SpriteMatrix() :
	width {0},
	height {0}
{}

// Actual constructor
SpriteMatrix::SpriteMatrix(int width_, int height_) :
	width {width_},
	height {height_} 
{
	// Allocate array of sprites (simulate a 2D array by mapping x/y coordinates
	// to y*width+x)
	sprites.resize(width*height);

	// Position sprites on grid
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			sprites[y*width + x].setPosition(GRID_SIZE*x, GRID_SIZE*y);
		}
	}

	// Allocate array of ints for tile information (collision data etc.)
	tileInfo.resize(width*height);
}


/*******************************************************************
 * Getters and setters
 *******************************************************************/

// Get Sprite at a certain position. Throws std::out_of_range exception if
// outside of matrix boundaries.
sf::Sprite& SpriteMatrix::getSprite(int x, int y) {
	return sprites[coordsToIndex(x, y)];
}

// Get tile information for a position (like collision data).
TileInfo& SpriteMatrix::getTileInfo(int x, int y) {
	return tileInfo[coordsToIndex(x, y)];
}

