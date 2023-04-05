
#include "SurfaceObjects.h"



bool SurfaceObjects::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
	// Load the tileset texture
	if (!o_tileset.loadFromFile("Images\\Objects_.png"))
		return false;

	// Resize the vertex array to fit the level size
	o_vertices.setPrimitiveType(sf::Quads);
	o_vertices.resize(width * height * 4);

	// Populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// Get the current tile number
			int tileNumber = tiles[i + j * width];

			// Find its position in the tileset texture
			int tileCol = tileNumber % (o_tileset.getSize().x / tileSize.x);
			int tileRow = tileNumber / (o_tileset.getSize().x / tileSize.x);

			// Get a pointer to the current tile's quad
			sf::Vertex* quad = &o_vertices[(i + j * width) * 4];

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
		}

	return true;
}

void SurfaceObjects::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply the transform
	states.transform *= getTransform();

	// Apply the tileset texture
	states.texture = &o_tileset;

	// Draw the vertex array
	target.draw(o_vertices, states);
}
