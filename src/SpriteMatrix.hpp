#ifndef SPRITEMATRIX_HPP_
#define SPRITEMATRIX_HPP_

#include <SFML/Graphics.hpp>

#include "TileInfo.hpp"

class SpriteMatrix {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	SpriteMatrix();
	SpriteMatrix(int width_, int height_);
	~SpriteMatrix();

	// Forbid copy, but allow move operations
	SpriteMatrix(const SpriteMatrix& other)            = delete;  // copy constructor
	SpriteMatrix& operator=(const SpriteMatrix& other) = delete;  // copy assignment
	SpriteMatrix(SpriteMatrix&& other);                           // move constructor (custom)
	SpriteMatrix& operator=(SpriteMatrix&& other);                // move assignment (custom)


	/*******************************************************************
	 * Getters and setters
	 *******************************************************************/
	// Get Sprite at a certain position. Throws std::out_of_range exception if
	// outside of matrix boundaries.
	sf::Sprite& getSprite(int x, int y);

	// Get tile information for a position (like collision data).
	TileInfo& getTileInfo(int x, int y);


	/*******************************************************************
	 * Helper functions
	 *******************************************************************/
	// Transforms x,y coordinates to array index, throws exception if out of bounds
	int coordsToIndex(int x, int y) {
		// Transform coordinates
		int index = y*width + x;

		// Check if index is in array boundaries
		if (index >= width*height) {
			// TODO Test this
			throw std::out_of_range("Coordinates" + std::to_string(x) + ", " + std::to_string(y)
				+ " are out of SpriteMatrix boundaries");
		}

		return index;
	}


	/*******************************************************************
	 * Data
	 *******************************************************************/
	// Matrix size
	int width;
	int height;

	// Tile grid size
	// TODO make this variable somehow
	const int GRID_SIZE = 32;

private:
	// Sprite field
	sf::Sprite* sprites;

	// A second field of integers to store tile information (like collision data)
	TileInfo* tileInfo;
};

#endif /* SPRITEMATRIX_HPP_ */
