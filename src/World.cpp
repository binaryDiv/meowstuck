#include "World.hpp"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


/*******************************************************************
 * Construction and destruction
 *******************************************************************/

World::World() {
}


/*******************************************************************
 * Loading, Resource Management
 *******************************************************************/

// Load world data from JSON file
void World::loadFromFile(const std::string& filename) {
	// Open file stream
	std::ifstream ifs (filename);

	if (!ifs) {
		std::cerr << "[World::loadFromFile] ERROR: could not open file '" << filename << "'" << std::endl;
		return;
	}

	try {
		// Read JSON data
		json j;
		ifs >> j;

		// Some debug output
		std::string worldTitle = j.value("title", "Unnamed");
		std::cout << "Loaded world '" << worldTitle << "' with "
		          << j["rooms"].size() << " rooms\n\n";

		for (auto& el : j["rooms"].items()) {
			std::cout << "Room '" << el.key() << "': " << el.value() << "\n";
		}

		// Dump JSON data for debugging
		std::cout << "\nJSON data:\n";
		std::cout << j.dump(4) << std::endl;
	}
	catch (json::parse_error& e) {
		std::cerr << "[World::loadFromFile] ERROR: " << e.what() << std::endl;
		return;
	}
	catch (json::type_error& e) {
		std::cerr << "[World::loadFromFile] ERROR: " << e.what() << std::endl;
		return;
	}
}

