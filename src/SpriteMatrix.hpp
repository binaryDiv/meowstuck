#ifndef SPRITEMATRIX_HPP_
#define SPRITEMATRIX_HPP_

#include <stdexcept>
#include <SFML/Graphics.hpp>

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

	// Set Sprite at a certain position in the matrix and update the Sprite's position
	// accordingly. Overwrite the existing Sprite (if any).
	// Throws std::out_of_range exception if outside of matrix boundaries.
	// TODO Is this function necessary or can we also set sprite via getSprite() = sprite?
	void setSprite(int x, int y, sf::Sprite newSprite);


	/*******************************************************************
	 * Data
	 *******************************************************************/
	// Matrix size
	int width;
	int height;

private:
	// Sprite field
	sf::Sprite* sprites;
};

#endif /* SPRITEMATRIX_HPP_ */
