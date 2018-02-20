#include <SFML/Graphics.hpp>

#include "World.hpp"

#include <algorithm>
#include <iostream>
#include <string>

const int SCREEN_WIDTH  = 512;
const int SCREEN_HEIGHT = 512;

int main() {
	// Create main window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_WIDTH), "...");

	// Control the framerate
	window.setVerticalSyncEnabled(true);


	// Load world file
	World world;
	world.loadFromFile("res/world.json");

	// Set window title to world's title
	window.setTitle(world.title);

	// Get a reference to a room
	// TODO Read name of start room from world data
	Room& currentRoom = world.getRoom("startroom");

	//return 0;


	// Play music
	// TODO Really. Do it. Something.
	
	while (window.isOpen()) {
		// Process events
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					// Close window -> exit
					window.close();
					break;
				
				case sf::Event::Resized:
					// Resize window -> rescale view to keep aspect ratio
					{
						int newWidth = event.size.width;
						int newHeight = event.size.height;

						std::cout << "new width: " << newWidth << ", height: " << newHeight << std::endl;

						// Create new view with the size of the screen
						sf::View resizedView (
							sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2),
							sf::Vector2f(newWidth, newHeight)
						);

						// Zoom view without stretching
						resizedView.zoom(std::max(SCREEN_WIDTH / (float) newWidth, SCREEN_HEIGHT / (float) newHeight));

						// Set view
						window.setView(resizedView);
					}
					break;

				default:
					break;
			}
		}

		// Clear screen
		window.clear();

		// Draw room
		for (int y = 0; y < currentRoom.getHeight(); y++) {
			for (int x = 0; x < currentRoom.getWidth(); x++) {
				// Draw single tile
				window.draw(currentRoom.tileField.getSprite(x, y));
			}
		}

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}

