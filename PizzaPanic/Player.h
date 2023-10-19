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

	void move(sf::Time deltaTime);
	void animate();
	void checkCollisions(const TileMap& objects);
	void PlayerLife(float QuitarVida, float xPlayer, float yPlayer);
	void PlayerLifeAux(float xPlayer, float yPlayer);

	const float playerWidht = 320.f;
	const float playerHeight = 320.f;
	 float initialX = 1345.f;
	 float initialY = 1390.f;
	const float escaleX = 0.18;
	const float escaleY = 0.18;

	sf::Vector2f previousPos;
	

	sf::RectangleShape playerLife;
	sf::RectangleShape playerLifeAux;

	sf::IntRect texRect;
	sf::Sprite sprite;
	sf::Texture texture;

	const float speed = 450.f;
	const float playerFullLife = 60.f;
};

