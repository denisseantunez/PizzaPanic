
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

	bool load(const std::string& tileset, sf::Vector2u tileSize, int layer);

	void updateDayNightCycle(sf::Clock& clock);
	std::vector<sf::FloatRect> collidables;
	
private:
	virtual sf::Color colorInterpolation(float alpha);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;


	sf::Color currentColor;

	
};


