// tutorial sobre esto en https://www.sfml-dev.org/tutorials/2.4/graphics-vertex-array.php#example-tile-map :)
// modificación para que obtenga los índices mediante un .txt https://en.sfml-dev.org/forums/index.php?topic=14216.0


#include "TileMap.h"



bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize)
{
	// Load the tileset texture
	if (!m_tileset.loadFromFile("Images\\Tileset.png"))
		return false;

	// .txt tilemap
	std::vector<std::vector<int> > tiles;
	std::ifstream map_stream("Tilemaps\\background.txt");
	for (std::string line; std::getline(map_stream, line);){
		tiles.push_back(std::vector<int>());
		std::stringstream line_stream(line);
		std::copy(std::istream_iterator<int>(line_stream), std::istream_iterator<int>(), std::back_inserter(tiles.back()));
	}


	unsigned int height = tiles.size();

	m_vertices.setPrimitiveType(sf::Quads);


	// Populate the vertex array, with one quad per tile
	for (unsigned int j = 0; j < height; ++j){ 

		unsigned int width = tiles[j].size();

		for (unsigned int i = 0; i < width; ++i){
			// Get the current tile number 
			int tileNumber = tiles[j][i];

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

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply the transform
	states.transform *= getTransform();

	// Apply the tileset texture
	states.texture = &m_tileset;

	// Draw the vertex array
	target.draw(m_vertices, states);
}

