#ifndef COORDUTILS_HPP_
#define COORDUTILS_HPP_

#include <string>

// Coordinate pair (typedeffed std::pair<int,int>)
typedef std::pair<int, int> CoordXY;

// Tupel of x and y coordinates and room name
class CoordRoomXY {
public:
	CoordRoomXY() {};
	CoordRoomXY(std::string room, int x, int y) :
		room {room},
		x {x},
		y {y}
	{}

	// Room name
	std::string room;
	int x;
	int y;
};

#endif /* COORDUTILS_HPP_ */
