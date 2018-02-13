#include "Room.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


/*******************************************************************
 * Construction and destruction
 *******************************************************************/

Room::Room() {
}

Room::Room(const std::string& name, int width, int height) {
	this->name = name;

	// Create tile field
	this->tileField = SpriteMatrix(width, height);
}


/*******************************************************************
 * Loading
 *******************************************************************/

// Helper function: convert hexadecimal digit character (0-9, a-f, A-F) to int,
// return -1 for invalid characters
static int hexDigitToInt(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	}
	else if (c >= 'a' && c <= 'f') {
		return c - 'a' + 10;
	}
	else {
		return -1;
	}
}

// Parse tile data from a JSON array of strings and create sprite field
// TODO This function is so bloated... split it somehow?
void Room::loadTileData(json& tileData) {
	// Current x,y coordinates
	int x = 0;
	int y = 0;

	// Parse each row
	for (auto& rowData : tileData) {
		// Error if y (row) coordinate is out of boundaries
		if (y >= tileField.height) {
			// TODO Custom exception?
			throw std::runtime_error("More input rows than tile field rows");
		}

		// Reset x (column) coordinate
		x = 0;

		std::string rowStr = rowData;
		std::cout << "Tile row: " << rowStr << "\n";

		// State variables
		int tileID = 0;
		int readState = 0;

		// Iterate over the string, character-wise
		for (std::string::iterator it = rowStr.begin(); it != rowStr.end(); it++) {
			char c = *it;
			int digit = hexDigitToInt(c);

			// Check for generally not allowed characters
			if (c != ' ' && digit < 0) {
				// Invalid character
				// TODO Custom exception?
				std::string e ("Invalid character '" + std::to_string(c)
					+ "' in line " + std::to_string(y));
				throw std::runtime_error(e);
			}

			// Error if reading another hex digit and x (column) coordinate is out of boundaries
			if (digit >= 0 && x >= tileField.width) {
				// TODO Custom exception?
				throw std::runtime_error("More input columns than tile field columns in line "
					+ std::to_string(y));
			}

			if (readState == 0) {
				// Initial state: look for first hex digit
				if (c == ' ') {
					// Skip spaces
					continue;
				}
				else if (digit >= 0) {
					// Add first digit to tileID
					tileID = digit;

					// Set next state
					readState = 1;
				}
			}
			else if (readState == 1) {
				// Second state: found first hex digit, look for second digit
				if (digit >= 0) {
					// Add second digit to tileID -> tileID complete
					tileID = tileID * 16 + digit;

					// Set tile at position
					setTile(x, y, tileID);

					// Increment x (column)
					x++;

					// Reset tileID
					tileID = 0;

					// Set next state
					readState = 2;
				}
				else if (c == ' ') {
					// Space not allowed here
					// TODO Custom exception?
					std::string e ("Unexpected space after only one hex digit, in line "
						+ std::to_string(y));
					throw std::runtime_error(e);
				}
			}
			else if (readState == 2) {
				// Third state: found two hex digits, look for a space (or end of string)
				if (c == ' ') {
					// Okay, go back to initial state
					readState = 0;
				}
				else {
					// Only two hex digits are allowed
					// TODO Custom exception?
					std::string e("Unexpected hex digit after reading two hex digits, "
						"in line " + std::to_string(y));
					throw std::runtime_error(e);
				}
			}
			else {
				// This should actually not happen.
				throw std::logic_error("invalid readState!");
			}
		}

		// Increment y (row) coordinate
		y++;
	}
}

// Set tile at a specific position to a tile referenced by its ID
void Room::setTile(int x, int y, int tileID) {
	std::cout << "set tile " << tileID << " at " << x << "," << y << std::endl;

	// Get Sprite
	// TODO
}

