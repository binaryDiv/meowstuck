#include <cstdlib>
#include "GameEngine.hpp"

const int SCREEN_WIDTH  = 512;
const int SCREEN_HEIGHT = 512;

int main() {
	// Create instance of game engine
	GameEngine engine (SCREEN_WIDTH, SCREEN_HEIGHT);

	// Load game data
	engine.loadFromFile("res/world.json");

	// Run main loop
	engine.run();

	// TODO Error handling (catch exceptions)

	return EXIT_SUCCESS;
}

