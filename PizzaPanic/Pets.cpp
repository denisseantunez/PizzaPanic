
#include "Pets.h"

void Pets::hitbox(const float x, const float y, const float width, const float height)
{
	this->petHitbox.setPosition(x, y);
	this->petHitbox.setSize(sf::Vector2f(width, height));
	this->petHitbox.setFillColor(sf::Color::Transparent);
	this->petHitbox.setOutlineColor(sf::Color::Transparent);
	this->petHitbox.setOutlineThickness(6.f);
}

void Pets::animate(sf::Sprite pet, float xPlayer, float yPlayer, const float petSpeed, float initialX, float initialY)
{
	float petAngle = this->petAngle(xPlayer, yPlayer, petHitbox.getPosition().x, petHitbox.getPosition().y, initialX, initialY, petSpeed);

	if ((petAngle >= 70 && petAngle <= 110) || (petAngle >= -290 && petAngle <= -250)) { // ARRIBA
		petTexRect.top = 498;
		if (petTexRect.left == 572)
			petTexRect.left = 468;
		else
			petTexRect.left += 52;
	}
	else if (petAngle > 110 && petAngle < 250) { // DERECHA
		petTexRect.top = 429;
		if (petTexRect.left == 572)
			petTexRect.left = 468;
		else
			petTexRect.left += 52;
	}
	else if ((petAngle >= 250 && petAngle <= 290) || (petAngle >= -110 && petAngle <= -70)) { // ABAJO
		petTexRect.top = 287;
		if (petTexRect.left == 572)
			petTexRect.left = 468;
		else
			petTexRect.left += 52;
	}
	else {
		if (petAngle > 0 || (petAngle > -250 && petAngle < -110)) { // IZQUIERDA
			petTexRect.top = 358; // IZQUIERDA
			if (petTexRect.left == 572)
				petTexRect.left = 468;
			else
				petTexRect.left += 52;
		}
		else {
			petTexRect.top = 429; // DERECHA
			if (petTexRect.left == 572)
				petTexRect.left = 468;
			else
				petTexRect.left += 52;
		}
	}
	pet.setTextureRect(petTexRect);
}

void Pets::followPlayer(float xPlayer, float yPlayer, float initialX, float initialY, const float petSpeed, sf::Time deltaTime)
{
	float xPet = petHitbox.getPosition().x;
	float yPet = petHitbox.getPosition().y;

	float dx = xPlayer - xPet;
	float dy = yPlayer - yPet;
	float distance = sqrt(pow(dx, 2.f) + pow(dy, 2.f));

	float dxaux = initialX - xPet;
	float dyaux = initialY - yPet;
	float distanceaux = sqrt(pow(dxaux, 2.f) + pow(dyaux, 2.f));

	sf::Vector2f unitVector(dx / distance, dy / distance);
	sf::Vector2f unitVectoraux(dxaux / (distanceaux + 0.1), dyaux / (distanceaux + 0.1));
	
	sf::Vector2f velocity = unitVector * (petSpeed);
	sf::Vector2f velocityaux = unitVectoraux * (petSpeed);

	if (distance <= RadioDetected && distanceaux <= RadioDetected)
		petHitbox.move(velocity * deltaTime.asSeconds());
	else 
		petHitbox.move(velocityaux * deltaTime.asSeconds());
	
}

void Pets::checkMordidas(float& mordidas, float& quitarVida, sf::FloatRect playerCollider)
{
	sf::FloatRect petCollider = petHitbox.getGlobalBounds();

	if (petCollider.intersects(playerCollider))
	{
		mordidas++;
		if (mordidas > 0 && mordidas < 120)
			quitarVida += 0.5f;
	}
}

float Pets::petAngle(float xPlayer, float yPlayer, float xPet, float yPet, float initialX, float initialY, const float petSpeed) {
	float dx = xPlayer - xPet;
	float dy = yPlayer - yPet;
	float distance = sqrt(pow(dx, 2.f) + pow(dy, 2.f));

	float dxaux = initialX - xPet;
	float dyaux = initialY - yPet;
	float distanceaux = sqrt(pow(dxaux, 2.f) + pow(dyaux, 2.f));

	sf::Vector2f unitVector(dx / distance, dy / distance);
	sf::Vector2f unitVectoraux(dxaux / (distanceaux + 0.1), dyaux / (distanceaux + 0.1));

	sf::Vector2f velocity = unitVector * (petSpeed);
	sf::Vector2f velocityaux = unitVectoraux * (petSpeed);

	if (distance <= RadioDetected && distanceaux <= RadioDetected) {
		float angle = atan2(velocity.y, velocity.x) * 180 / 3.141592 + 180.f;
		return angle;
	}
	else {
		float angle = atan2(velocityaux.y, velocityaux.x) * 180 / 3.141592 + 180.f;
		return angle;
	}
}
