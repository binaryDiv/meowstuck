#include "SpriteMatrix.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

/*******************************************************************
 * Construction and destruction
 *******************************************************************/
// Default constructor
SpriteMatrix::SpriteMatrix() :
	width {0},
	height {0},
	sprites {nullptr}
{}

// Actual constructor
SpriteMatrix::SpriteMatrix(int width_, int height_) :
	width {width_},
	height {height_} 
{
	// Allocate array of sprites (simulate a 2D array by mapping x/y coordinates
	// to y*width+x)
	sprites = new sf::Sprite[width*height];
}

// Destructor
SpriteMatrix::~SpriteMatrix() {
	// Free resources
	if (sprites != nullptr) {
		delete[] sprites;
		sprites = nullptr;
	}
}

// Move constructor
SpriteMatrix::SpriteMatrix(SpriteMatrix&& other) {
	// Steal data from other object
	width = other.width;
	height = other.height;
	sprites = other.sprites;

	// Reset other object to default state
	other.width = 0;
	other.height = 0;
	other.sprites = nullptr;
}

// Move assignment
SpriteMatrix& SpriteMatrix::operator=(SpriteMatrix&& other) {
	// Reset this object first, free resources
	if (sprites != nullptr) {
		delete[] sprites;
		sprites = nullptr;
	}

	// Steal data from other object
	width = other.width;
	height = other.height;
	sprites = other.sprites;

	// Reset other object to default state
	other.width = 0;
	other.height = 0;
	other.sprites = nullptr;

	return *this;
}


/*******************************************************************
 * Getters and setters
 *******************************************************************/
// Get Sprite at a certain position. Throws std::out_of_range exception if
// outside of matrix boundaries.
sf::Sprite& SpriteMatrix::getSprite(int x, int y) {
	// Transform x,y coordinates to array index
	int index = y*width + x;

	// Check if index is in array boundaries
	if (index >= width*height) {
		// TODO Test this
		std::string e ("Coordinates" + std::to_string(x) + ", " + std::to_string(y)
			+ " are out of SpriteMatrix boundaries");
		throw std::out_of_range(e);
	}

	return sprites[index];
}

// Set Sprite at a certain position in the matrix and update the Sprite's position
// accordingly. Overwrite the existing Sprite (if any).
// Throws std::out_of_range exception if outside of matrix boundaries.
void SpriteMatrix::setSprite(int x, int y, sf::Sprite newSprite) {
	// Transform x,y coordinates to array index
	int index = y*width + x;

	// Check if index is in array boundaries
	if (index >= width*height) {
		// TODO Test this
		std::string e ("Coordinates" + std::to_string(x) + ", " + std::to_string(y)
			+ " are out of SpriteMatrix boundaries");
		throw std::out_of_range(e);
	}

	sprites[index] = newSprite;
}


