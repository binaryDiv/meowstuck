#include <SFML/Graphics.hpp>

#include "World.hpp"

#include <algorithm>
#include <iostream>
#include <string>

const int SCREEN_WIDTH  = 512;
const int SCREEN_HEIGHT = 512;
const int FIELD_WIDTH   = 16;
const int FIELD_HEIGHT  = 16;
const int GRID_SIZE     = 32;

int main() {
	// Create main window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_WIDTH), "...");

	// Control the framerate
	window.setVerticalSyncEnabled(true);


	// Load world file
	World world;
	world.loadFromFile("res/world.json");

	window.setTitle(world.title);

	//return 0;


	// Load some textures
	sf::Texture texture_cat, texture_empty, texture_block;
	if (   !texture_cat.loadFromFile("res/cat.png")
		|| !texture_empty.loadFromFile("res/empty.png")
		|| !texture_block.loadFromFile("res/block.png") ) {
		return EXIT_FAILURE;
	}

	// Create sprites
	sf::Sprite sprite_cat (texture_cat);
	sf::Sprite sprite_empty (texture_empty);
	sf::Sprite sprite_block (texture_block);
	//sprite.setScale(sf::Vector2f(16.0, 16.0));

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

		// Draw sprites
		for (int y = 0; y < FIELD_HEIGHT; y++) {
			for (int x = 0; x < FIELD_WIDTH; x++) {
				// XXX quick and dirty... this is crappy but w/e
				sf::Sprite spr;

				if (x == 0 || x == FIELD_WIDTH-1 || y == 0 || y == FIELD_HEIGHT-1) {
					spr = sprite_empty;
				}
				else if (x == 1 || x == FIELD_WIDTH-2 || y == 1 || y == FIELD_HEIGHT-2) {
					spr = sprite_block;
				}
				else if (x == 4 && y == 3) {
					spr = sprite_cat;
				}
				else {
					spr = sprite_empty;
				}

				spr.setPosition(GRID_SIZE*x, GRID_SIZE*y);

				window.draw(spr);
			}
		}

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}

