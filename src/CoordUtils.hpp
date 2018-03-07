#ifndef COORDUTILS_HPP_
#define COORDUTILS_HPP_

#include <string>

// Coordinate pair
struct CoordXY {
	// Coordinates
	int x;
	int y;

	friend bool operator<(const CoordXY& lhs, const CoordXY& rhs) {
		return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
	}
};

// Tupel of x and y coordinates and room name
struct CoordRoomXY {
	// Room name
	std::string room;

	// Coordinates in room
	int x;
	int y;
};

#endif /* COORDUTILS_HPP_ */
