#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include <string>
#include <SFML/Graphics.hpp>

#include "World.hpp"

class GameEngine {
public:
	/*******************************************************************
	 * Construction and destruction
	 *******************************************************************/
	GameEngine();
	GameEngine(int screenWidth_, int screenHeight_);

	// Forbid copy and move operations
	GameEngine(const GameEngine& other)            = delete;  // copy constructor
	GameEngine& operator=(const GameEngine& other) = delete;  // copy assignment
	GameEngine(GameEngine&& other)                 = delete;  // move constructor
	GameEngine& operator=(GameEngine&& other)      = delete;  // move assignment


	/*******************************************************************
	 * Initialization and loading
	 *******************************************************************/
	// Load world data from JSON file
	void loadFromFile(const std::string& filename);


	/*******************************************************************
	 * Game loop
	 *******************************************************************/
	// Run game loop
	void run();

	// Process events
	void processEvents();

	// Update game (called every frame)
	void update();

	// Draw game (called every frame)
	void draw();


	/*******************************************************************
	 * Window and graphics stuff
	 *******************************************************************/
private:
	// Window dimensions
	int screenWidth;
	int screenHeight;

	// SFML window
	sf::RenderWindow window;


	/*******************************************************************
	 * Game data
	 *******************************************************************/
private:
	// World instance
	World world;
};

#endif /* GAMEENGINE_HPP_ */
