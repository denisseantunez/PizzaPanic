#pragma once

#include <SFML/Graphics.hpp>

#include "TileMap.h"

class Pet 
{
public:
	sf::RectangleShape hitbox;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect texRect;
	float speed = 250.f;

	void setHitbox(const float x, const float y, const float width, const float height);

	void animate(float xPlayer, float yPlayer, float initialX, float initialY);
	void animate(float xPlayer, float yPlayer, float chiwisSpeed);

	void followPlayer(float xPlayer, float yPlayer, float initialX, float initialY, sf::Time deltaTime);
	void followPlayer(sf::Sprite mPlayer, const float chiwisRadio, float chiwisSpeed, sf::Time deltaTime);

	void checkMordidas(float& mordidas, float& quitarVida, sf::FloatRect playerBounds);

	void checkCollisions(const TileMap& objects, sf::Time deltaTime, const float petSpeed);

private:
	const float RadioDetected = 300.f;

	float petAngle(float xPlayer, float yPlayer, float xPet, float yPet, float initialX, float initialY);
	float chiwisAngle(float xPlayer, float yPlayer, float xPet, float yPet, const float chiwisSpeed);

	
};
