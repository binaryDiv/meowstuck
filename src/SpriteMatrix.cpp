#include "SpriteMatrix.hpp"

#include <stdexcept>

/*******************************************************************
 * Construction and destruction
 *******************************************************************/

// Default constructor
SpriteMatrix::SpriteMatrix() :
	width {0},
	height {0},
	sprites {nullptr},
	tileInfo {nullptr}
{}

// Actual constructor
SpriteMatrix::SpriteMatrix(int width_, int height_) :
	width {width_},
	height {height_} 
{
	// Allocate array of sprites (simulate a 2D array by mapping x/y coordinates
	// to y*width+x)
	sprites = new sf::Sprite[width*height];

	// Position sprites on grid
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			sprites[y*width + x].setPosition(GRID_SIZE*x, GRID_SIZE*y);
		}
	}

	// Allocate array of ints for tile information (collision data etc.)
	tileInfo = new TileInfo[width*height];
}

// Destructor
SpriteMatrix::~SpriteMatrix() {
	// Free resources
	if (sprites != nullptr) {
		// Sprite field
		delete[] sprites;
		sprites = nullptr;
	}

	if (tileInfo != nullptr) {
		// TileInfo field
		delete[] tileInfo;
		tileInfo = nullptr;
	}
}

// Move constructor
SpriteMatrix::SpriteMatrix(SpriteMatrix&& other) {
	// Steal data from other object
	width = other.width;
	height = other.height;
	sprites = other.sprites;
	tileInfo = other.tileInfo;

	// Reset other object to default state
	other.width = 0;
	other.height = 0;
	other.sprites = nullptr;
	other.tileInfo = nullptr;
}

// Move assignment
SpriteMatrix& SpriteMatrix::operator=(SpriteMatrix&& other) {
	// Reset this object first, free resources
	if (sprites != nullptr) {
		// Sprite field
		delete[] sprites;
		sprites = nullptr;
	}

	if (tileInfo != nullptr) {
		// TileInfo field
		delete[] tileInfo;
		tileInfo = nullptr;
	}

	// Steal data from other object
	width = other.width;
	height = other.height;
	sprites = other.sprites;
	tileInfo = other.tileInfo;

	// Reset other object to default state
	other.width = 0;
	other.height = 0;
	other.sprites = nullptr;
	other.tileInfo = nullptr;

	return *this;
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

