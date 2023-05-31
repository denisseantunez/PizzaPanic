#pragma once
#include <SFML/Graphics.hpp>

class Player
{

public:

	Player();

	//Player's Movement
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	bool mIsMovingUp = false;
	bool mIsMovingDown = false;
	bool mIsMovingLeft = false;
	bool mIsMovingRight = false;

	void setHitbox(const float x, const float y, const float width, const float height);
	void PlayerLife(float QuitarVida, float xPlayer, float yPlayer);
	void PlayerLifeAux(float xPlayer, float yPlayer);

	const float playerWidht = 320.f;
	const float playerHeight = 320.f;
	const float initialX = 2500.f;
	const float initialY = 2500.f;
	const float escaleX = 0.18;
	const float escaleY = 0.18;


	sf::RectangleShape hitbox;
	sf::RectangleShape playerLife;
	sf::RectangleShape playerLifeAux;
	sf::IntRect texRect;
	sf::Sprite sprite;
	sf::Texture texture;

	const float speed = 250.f;
	const float playerFullLife = 100.f;
	
};

