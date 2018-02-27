#include "GameEngine.hpp"

#include <algorithm>
#include <iostream>

#include "World.hpp"


/*******************************************************************
 * Construction and destruction
 *******************************************************************/

// Default constructor
GameEngine::GameEngine() {
}

// Actual constructor that creates the window
GameEngine::GameEngine(int screenWidth_, int screenHeight_) :
	screenWidth {screenWidth_},
	screenHeight {screenHeight_}
{
	// Create main window
	window.create(sf::VideoMode(screenWidth, screenHeight), "...");

	// Control the framerate
	window.setVerticalSyncEnabled(true);
}


/*******************************************************************
 * Initialization and loading
 *******************************************************************/

// Load world data from JSON file
void GameEngine::loadFromFile(const std::string& filename) {
	// Load world file
	world.loadFromFile(filename);

	// Set window title to world's title
	window.setTitle(world.title);
}


/*******************************************************************
 * Game loop
 *******************************************************************/

// Run game loop
void GameEngine::run() {
	// TODO Play music

	// Game loop until window has been closed
	while (window.isOpen()) {
		// Process events
		processEvents();

		// Update game logic
		update();

		// Draw frame
		draw();
	}
}

// Process events
void GameEngine::processEvents() {
	sf::Event event;

	// Poll events
	while (window.pollEvent(event)) {
		switch (event.type) {
			// Close window -> exit
			case sf::Event::Closed:
				window.close();
				break;
			
			// Resize window -> rescale view to keep aspect ratio
			case sf::Event::Resized:
				{
					int newWidth = event.size.width;
					int newHeight = event.size.height;

					std::cout << "new width: " << newWidth << ", height: " << newHeight << std::endl;

					// Create new view with the size of the screen
					sf::View resizedView (
						sf::Vector2f(screenWidth / 2, screenHeight / 2),
						sf::Vector2f(newWidth, newHeight)
					);

					// Zoom view without stretching
					resizedView.zoom(std::max(screenWidth / (float) newWidth, screenHeight / (float) newHeight));

					// Set view
					window.setView(resizedView);
				}
				break;

			default:
				break;
		}
	}
}

// Update game (called every frame)
void GameEngine::update() {
	// TODO do something?
}

// Draw game (called every frame)
void GameEngine::draw() {
	// Get a reference to the player entity
	SpriteEntity& playerEntity = world.getPlayer();

	// Get a reference to the current room
	Room& currentRoom = world.getRoom(playerEntity.roomName);

	// Clear screen
	window.clear();

	// Draw room
	for (int y = 0; y < currentRoom.getHeight(); y++) {
		for (int x = 0; x < currentRoom.getWidth(); x++) {
			// Draw single tile
			window.draw(currentRoom.tileField.getSprite(x, y));
		}
	}

	// Draw player sprite
	window.draw(playerEntity.getSprite());

	// Update the window
	window.display();
}

