#ifndef TILEINFO_HPP_
#define TILEINFO_HPP_

class TileInfo {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	// Default constructor
	TileInfo()
		: value {0}
	{}
	
	// Value constructor
	TileInfo(int value)
		: value {value}
	{}


	/*******************************************************************
	 * Data
	 *******************************************************************/
	// Tile info value
	int value;


	/*******************************************************************
	 * Flags
	 *******************************************************************/
	static const int FLAG_SOLID = 1;


	/*******************************************************************
	 * Flag getters
	 *******************************************************************/
	const bool isSolid() {
		return value & FLAG_SOLID;
	}
};

#endif /* TILEINFO_HPP_ */
