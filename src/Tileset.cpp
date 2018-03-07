#include "Tileset.hpp"

#include <stdexcept>

/*******************************************************************
 * Construction and destruction
 *******************************************************************/

Tileset::Tileset() {
}


/*******************************************************************
 * Loading
 *******************************************************************/

// Load tile set (as a sprite sheet) from an image file and extract
// textures for each tile.
void Tileset::loadTilesetFromFile(const std::string& filename) {
	// Try to load texture
	if (!texture.loadFromFile(filename)) {
		throw std::runtime_error("Loading tileset from file '" + filename + "' failed");
	}

	// Calculate number of tiles per row and column
	auto textureSize = texture.getSize();
	tilesPerRow = textureSize.x / tileSize;
	tilesPerColumn = textureSize.y / tileSize;
}


/*******************************************************************
 * Tile management
 *******************************************************************/

// Sets a Sprite's texture and texture rect by index of tile in tileset
void Tileset::setSpriteToTile(sf::Sprite& sprite, unsigned int tileIndex) const {
	// Set texture
	sprite.setTexture(texture);
	
	// Calculate tile's position in spritesheet
	int tileCol = tileIndex % tilesPerRow;
	int tileRow = tileIndex / tilesPerRow;

	// Error handling
	if (tileRow >= tilesPerColumn) {
		throw std::runtime_error("tileIndex " + std::to_string(tileIndex) + " is out of bounds");
	}

	// Set texture rect
	sprite.setTextureRect(sf::IntRect(tileCol * tileSize, tileRow * tileSize, tileSize, tileSize));
}

