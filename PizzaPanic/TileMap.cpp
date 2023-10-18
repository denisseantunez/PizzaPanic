

#include "TileMap.h"


/*******************************************************************************************************************************************************************/

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, bool collisions)
{
	// Load the tileset texture
	if (!m_tileset.loadFromFile("../Images/Tileset.png"))
		return false;

	// .txt tilemap
	std::ifstream map_stream;
	std::vector<std::vector<int> > tiles;
	if(collisions == false)
		map_stream.open("../Tilemaps/background.txt");
	else
		map_stream.open("../Tilemaps/surfaceobjects.txt");

	for (std::string line; std::getline(map_stream, line);){
		tiles.push_back(std::vector<int>());
		std::stringstream line_stream(line);
		std::copy(std::istream_iterator<int>(line_stream), std::istream_iterator<int>(), std::back_inserter(tiles.back()));
	}


	unsigned int height = tiles.size();

	m_vertices.setPrimitiveType(sf::Quads);
  f_vertices.setPrimitiveType(sf::Quads);


	// Populate the vertex array, with one quad per tile
	for (unsigned int j = 0; j < height; ++j){ 

		unsigned int width = tiles[j].size();

		for (unsigned int i = 0; i < width; ++i){
			// Get the current tile number 
			int tileNumber = tiles[j][i];

			// COLISIONS
			if (collisions == true && (tileNumber != -1 && tileNumber != 96 && tileNumber != 0 && tileNumber != 249)) { // tiles in .txt that are different from -1, 0 and 58 are not passable
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
      sf::Vertex fquad[4];

			// Define its 4 corners
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
      fquad[0].position = quad[0].position;
      fquad[1].position = quad[1].position;
      fquad[2].position = quad[2].position;
      fquad[3].position = quad[3].position;

			// Define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tileCol * tileSize.x, tileRow * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tileCol + 1) * tileSize.x, tileRow * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tileCol + 1) * tileSize.x, (tileRow + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tileCol * tileSize.x, (tileRow + 1) * tileSize.y);
      fquad[0].texCoords = sf::Vector2f(0 * tileSize.x, 0 * tileSize.y);
      fquad[1].texCoords = sf::Vector2f((0 + 1) * tileSize.x, 0 * tileSize.y);
      fquad[2].texCoords = sf::Vector2f((0 + 1) * tileSize.x, (0 + 1) * tileSize.y);
      fquad[3].texCoords = sf::Vector2f(0 * tileSize.x, (0 + 1) * tileSize.y);

			for (int k = 0; k < 4; ++k)
				m_vertices.append(quad[k]);
      for (int k = 0; k < 4; ++k)
        f_vertices.append(quad[k]);
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

	// Draw the vertex array
	target.draw(m_vertices, states);
  target.draw(f_vertices, states);
}

/*******************************************************************************************************************************************************************/

