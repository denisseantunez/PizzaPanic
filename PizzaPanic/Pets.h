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

	sf::FloatRect rect = sprite.getGlobalBounds();

	float width = rect.width;
	float height = rect.height;

	float speed = 100.f;

	void setHitbox(const float x, const float y);

	void animate(float xPlayer, float yPlayer, float initialX, float initialY);
	void animate(float xPlayer, float yPlayer, float chiwisSpeed);

	void followPlayer(float xPlayer, float yPlayer, float initialX, float initialY, sf::Time deltaTime);
	void followPlayer(sf::Sprite mPlayer, const float chiwisRadio, float chiwisSpeed, sf::Time deltaTime);

	void checkBites(float& mordidas, float& quitarVida, int PizzasEntregadas, sf::FloatRect playerCollider);

	void checkCollisions(const TileMap& objects, sf::Time deltaTime, const float petSpeed);

private:

	const float RadioDetected = 200.f;

	float petAngle(float xPlayer, float yPlayer, float xPet, float yPet, float initialX, float initialY);
	float chiwisAngle(float xPlayer, float yPlayer, float xPet, float yPet, const float chiwisSpeed);
};
