

#include "Player.h"
#include <cmath>

/*******************************************************************************************************************************************************************/

void Player::move(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);

	if (mIsMovingUp)
		movement.y -= speed;
	if (mIsMovingDown)
		movement.y += speed;
	if (mIsMovingLeft)
		movement.x -= speed;
	if (mIsMovingRight)
		movement.x += speed;
	if (movement.x != 0.f && movement.y != 0.f)
		movement = movement / std::sqrt(2.f);

	previousPos = sprite.getPosition();

	sprite.move(movement * deltaTime.asSeconds());
}

/*******************************************************************************************************************************************************************/

void Player::animate()
{
	if (texRect.left == 1920)
		texRect.left = 0;
	else 
		texRect.left += 320; 

	sprite.setTextureRect(texRect);
}

/*******************************************************************************************************************************************************************/

void Player::checkCollisions(const TileMap& objects)
{
  double scale = 0.1;
  sf::FloatRect bounds = sprite.getGlobalBounds();
  double new_width = bounds.width * scale;
  double new_height = bounds.height * scale;
  double new_left = bounds.left + (bounds.width - new_width) / 2.0;
  double new_top = bounds.top + (bounds.height - new_height) / 2.0;
  sf::FloatRect new_bounds = sf::FloatRect(new_left, new_top, new_width, new_height);
  
	for (const sf::FloatRect& collidable : objects.collidables) {
		if (collidable.intersects(new_bounds)) {
			sprite.setPosition(previousPos);
			break;
		  }
	}
}

/*******************************************************************************************************************************************************************/

void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W){
		mIsMovingUp = isPressed;
	}
	else if (key == sf::Keyboard::S){
		mIsMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::A){
		mIsMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::D){
		mIsMovingRight = isPressed;
	}
}

/*******************************************************************************************************************************************************************/

void Player::PlayerLife(float QuitarVida, float xPlayer, float yPlayer) {

	this->playerLife.setPosition(xPlayer - 2.f, yPlayer - 20.f);
	this->playerLife.setSize(sf::Vector2f(playerFullLife - QuitarVida, 10.f));

	if (QuitarVida >= playerFullLife - 1.f) 
		this->playerLife.setFillColor(sf::Color::Red);
	else 
		this->playerLife.setFillColor(sf::Color::Green);
	
	this->playerLife.setOutlineColor(sf::Color::Transparent);
	this->playerLife.setOutlineThickness(3.f);
}

/*******************************************************************************************************************************************************************/

void Player::PlayerLifeAux(float xPlayer, float yPlayer) {

	this->playerLifeAux.setPosition(xPlayer - 2.f, yPlayer - 20.f);
	this->playerLifeAux.setSize(sf::Vector2f(playerFullLife, 10.f));
	this->playerLifeAux.setFillColor(sf::Color::Red);
	this->playerLifeAux.setOutlineColor(sf::Color::Black);
	this->playerLifeAux.setOutlineThickness(3.f);
}

/*******************************************************************************************************************************************************************/
