
#include "TileMap.h"
#include <iostream>


/*******************************************************************************************************************************************************************/

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, int layer)
{
	// Load the tileset texture
	if (!m_tileset.loadFromFile("Images\\Tileset.png"))
		return false;

	// .txt tilemap
	std::ifstream map_stream;
	std::vector<std::vector<int> > tiles;

	if (layer == 0)
		map_stream.open("Tilemaps\\layer0.txt");
	else if (layer == 1)
		map_stream.open("Tilemaps\\layer1.txt");
	else
		map_stream.open("Tilemaps\\layer2.txt");

	for (std::string line; std::getline(map_stream, line);) {
		tiles.push_back(std::vector<int>());
		std::stringstream line_stream(line);
		std::copy(std::istream_iterator<int>(line_stream), std::istream_iterator<int>(), std::back_inserter(tiles.back()));
	}


	unsigned int height = tiles.size();

	m_vertices.setPrimitiveType(sf::Quads);


	// Populate the vertex array, with one quad per tile
	for (unsigned int j = 0; j < height; ++j) {

		unsigned int width = tiles[j].size();

		for (unsigned int i = 0; i < width; ++i) {
			// Get the current tile number 
			int tileNumber = tiles[j][i];

			// COLISIONS
			if (layer == 1 && tileNumber!= -1 && tileNumber != 0) {
				// Calculate the bounds of the title
				sf::FloatRect tileBounds(i * 48.f, j * 48.f, 48.f, 48.f);

				// Add it to a vector 
				collidables.push_back(tileBounds);
			}

			// Find its position in the tileset texture
			int tileCol = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tileRow = tileNumber / (m_tileset.getSize().x / tileSize.x);

			// Get a pointer to the current tile's quad
			sf::Vertex quad[4];


			// Define its 4 corners
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// Define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tileCol * tileSize.x, tileRow * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tileCol + 1) * tileSize.x, tileRow * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tileCol + 1) * tileSize.x, (tileRow + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tileCol * tileSize.x, (tileRow + 1) * tileSize.y);

			for (int k = 0; k < 4; ++k)
				m_vertices.append(quad[k]);
		}

	}

	return true;
}

/*******************************************************************************************************************************************************************/

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply the transform
	states.transform *= getTransform();

	// Apply the tileset texture
	states.texture = &m_tileset;

	// Apply current color to tile

	// Draw the vertex array
	target.draw(m_vertices, states);
}

/*******************************************************************************************************************************************************************/

void TileMap::updateDayNightCycle(sf::Clock& clock) 
{
	// Get the time since the clock started
	sf::Time elapsedTime = clock.getElapsedTime();

	// Calculate alpha (opacity component) based on time which is in between 0 and 1 (will gradually change from day color to night color)
	float alpha = elapsedTime.asSeconds() / 10;


	// If alpha exceeds 1 (night time) reset it to 0 (day time)
	if (alpha > 2.0f) {
		clock.restart();
		alpha = 0.0f;
	}
	if (alpha < 1) { // Day to night color transition
		currentColor = colorInterpolation(alpha);
	}else{ // Night to day color transition
		currentColor = colorInterpolation(2-alpha);
	}

	// Apply current color to tile
	for (size_t i = 0; i < m_vertices.getVertexCount(); i += 4) {
		for (int j = 0; j < 4; ++j)
			m_vertices[i + j].color = currentColor;
	}

}

sf::Color TileMap::colorInterpolation(float alpha) {
	// Day and night colors
	sf::Color dayColor(255, 254, 232);
	sf::Color nightColor(44, 0, 95);

	// Color 1 to color 2 transition
	sf::Uint8 r = static_cast<sf::Uint8>(dayColor.r + alpha * (nightColor.r - dayColor.r));
	sf::Uint8 g = static_cast<sf::Uint8>(dayColor.g + alpha * (nightColor.g - dayColor.g));
	sf::Uint8 b = static_cast<sf::Uint8>(dayColor.b + alpha * (nightColor.b - dayColor.b));
	sf::Uint8 a = static_cast<sf::Uint8>(dayColor.a + alpha * (nightColor.a - dayColor.a));

	return sf::Color(r, g, b, a);

}
