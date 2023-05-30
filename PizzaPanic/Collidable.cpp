
#include "Collidable.h"

int Collidable::getTileType() const
{
	return m_tileType;
}

const sf::FloatRect& Collidable::getBounds() const
{
	return m_bounds;
}

bool Collidable::isSolid() const
{
	return m_solid;
}

