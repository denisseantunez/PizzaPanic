#pragma once

#include <SFML/Graphics.hpp>

class Pet 
{
public:
	sf::RectangleShape petHitbox;
	//sf::IntRect petTexRect;

	void hitbox(const float x, const float y, const float width, const float height);
	void animate(sf::Sprite pet, sf::IntRect petTexRect, float xPlayer, float yPlayer, const float petSpeed, float initialX, float initialY);
	void followPlayer(float xPlayer, float yPlayer, float initialX, float initialY, const float petSpeed, sf::Time deltaTime);
	void checkMordidas(float& mordidas, float& quitarVida, sf::FloatRect playerBounds);

private:
	const float RadioDetected = 300.f;

	float petAngle(float xPlayer, float yPlayer, float xPet, float yPet, float initialX, float initialY, const float petSpeed);

	
};
