// tutorial sobre esto en https://www.sfml-dev.org/tutorials/2.4/graphics-vertex-array.php#example-tile-map :)

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string& tileset, sf::Vector2u tileSize, bool collisions);
	std::vector<sf::FloatRect> collidables;
	
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

	
};


