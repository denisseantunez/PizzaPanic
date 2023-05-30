#pragma once

#include <SFML/Graphics.hpp>

class Pet 
{
public:
	sf::RectangleShape hitbox;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect texRect;
	const float speed = 250.f;

	void setHitbox(const float x, const float y, const float width, const float height);
	void animate(float xPlayer, float yPlayer, float initialX, float initialY);
	void followPlayer(float xPlayer, float yPlayer, float initialX, float initialY, sf::Time deltaTime);
	void checkMordidas(float& mordidas, float& quitarVida, sf::FloatRect playerBounds);

private:
	const float RadioDetected = 300.f;

	float petAngle(float xPlayer, float yPlayer, float xPet, float yPet, float initialX, float initialY);

	
};
