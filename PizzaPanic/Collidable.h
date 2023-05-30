#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>



class Collidable
{
public:
	Collidable(int tileType, sf::FloatRect bounds, bool solid = true)
		: m_tileType(tileType)
		, m_bounds(bounds)
		, m_solid(solid)
	{}

	Collidable()
		: m_tileType(0)
		, m_bounds(sf::FloatRect(0.f, 0.f, 0.f, 0.f))
		, m_solid(false)
	{}


	int getTileType() const;
	const sf::FloatRect& getBounds() const;
	bool isSolid() const;

	sf::FloatRect m_bounds; // The bounding rectangle of the collidable object

public:
	int m_tileType;
	bool m_solid;

};
