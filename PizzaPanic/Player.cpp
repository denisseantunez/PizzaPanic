#include "Player.h"

Player::Player() {

}

void Player::setHitbox(const float x, const float y, const float width, const float height)
{
	hitbox.setPosition(x, y);
	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(6.f);
}

/*******************************************************************************************************************************************************************/

void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	switch (key)
	{
	case sf::Keyboard::W:
		mIsMovingUp = isPressed;
		break;
	case sf::Keyboard::S:
		mIsMovingDown = isPressed;
		break;
	case sf::Keyboard::A:
		mIsMovingLeft = isPressed;
		break;
	case sf::Keyboard::D:
		mIsMovingRight = isPressed;
		break;
	default:
		break;
	}
}

void Player::PlayerLife(float QuitarVida, float xPlayer, float yPlayer) {

	this->playerLife.setPosition(xPlayer - 2.f, yPlayer - 20.f);
	this->playerLife.setSize(sf::Vector2f(playerFullLife - QuitarVida, 10.f));

	if (QuitarVida >= playerFullLife - 1.f) {
		this->playerLife.setFillColor(sf::Color::Red);
	}
	else {
		this->playerLife.setFillColor(sf::Color::Green);
	}
	this->playerLife.setOutlineColor(sf::Color::Transparent);
	this->playerLife.setOutlineThickness(3.f);


}

void Player::PlayerLifeAux(float xPlayer, float yPlayer) {

	this->playerLifeAux.setPosition(xPlayer - 2.f, yPlayer - 20.f);
	this->playerLifeAux.setSize(sf::Vector2f(playerFullLife, 10.f));
	this->playerLifeAux.setFillColor(sf::Color::Red);
	this->playerLifeAux.setOutlineColor(sf::Color::Black);
	this->playerLifeAux.setOutlineThickness(3.f);
}
