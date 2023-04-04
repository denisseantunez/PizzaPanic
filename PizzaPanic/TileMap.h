#pragma once

#include <SFML/Graphics.hpp>
#include <string>

// tutorial sobre esto en https://www.sfml-dev.org/tutorials/2.4/graphics-vertex-array.php#example-tile-map :)

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};

const int level[] =
{
	1, 1, 1, 2, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 2, 1, 1, 1, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 2, 2, 2, 2,
	1, 1, 4, 4, 3, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2,
	1, 1, 4, 1, 2, 1, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2,
	1, 1, 1, 1, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 2, 2, 2, 2,
	1, 1, 1, 1, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 2, 2, 2, 2,
	2, 1, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2,
	1, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
	1, 1, 1, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 2, 0, 0, 1, 0, 2, 2, 2, 2,
	1, 1, 0, 0, 0, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2,
	1, 1, 1, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 2, 1, 0, 1, 0, 2, 2, 2, 2,
	1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2,
	1, 1, 1, 1, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 2, 2, 2, 2,

};