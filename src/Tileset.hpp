#ifndef TILESET_HPP_
#define TILESET_HPP_

#include <SFML/Graphics.hpp>
#include <string>

class Tileset {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	Tileset();

	// Forbid copy, but allow move operations
	Tileset(const Tileset& other)            = delete;  // copy constructor
	Tileset& operator=(const Tileset& other) = delete;  // copy assignment
	Tileset(Tileset&& other)                 = default;  // move constructor
	Tileset& operator=(Tileset&& other)      = default;  // move assignment


	/*******************************************************************
	 * Loading
	 *******************************************************************/
	// Load tile set (as a sprite sheet) from an image file and extract
	// textures for each tile.
	void loadTilesetFromFile(const std::string& filename);


	/*******************************************************************
	 * Tile management
	 *******************************************************************/
	// Sets a Sprite's texture and texture rect by index of tile in tileset
	void setSpriteToTile(sf::Sprite& sprite, unsigned int tileIndex) const;


	/*******************************************************************
	 * Data
	 *******************************************************************/
private:
	// Spritesheet texture
	sf::Texture texture;

	// Size per tile in pixel (defaults to 32 for our spritesheets)
	int tileSize = 32;

	// Size of spritesheet in tiles per row/column
	int tilesPerRow = 0;
	int tilesPerColumn = 0;
};

#endif /* TILESET_HPP_ */
