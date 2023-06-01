#pragma once
#include <SFML/Graphics.hpp>

#include "TileMap.h"

class Player
{

public:
	
	//Player's Movement
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	bool mIsMovingUp = false;
	bool mIsMovingDown = false;
	bool mIsMovingLeft = false;
	bool mIsMovingRight = false;

	//void setHitbox();
	void move(sf::Time deltaTime);
	void animate();
	void checkCollisions(const TileMap& objects);
	void PlayerLife(float QuitarVida, float xPlayer, float yPlayer);
	void PlayerLifeAux(float xPlayer, float yPlayer);

	const float playerWidht = 320.f;
	const float playerHeight = 320.f;
	const float initialX = 2500.f;
	const float initialY = 2500.f;
	const float escaleX = 0.18;
	const float escaleY = 0.18;

	sf::Vector2f previousPos;


	sf::RectangleShape playerLife;
	sf::RectangleShape playerLifeAux;
	sf::IntRect texRect;
	sf::Sprite sprite;
	sf::Texture texture;
	//sf::FloatRect hitbox;


	const float speed = 500.f;
	const float playerFullLife = 60.f;
	
};

