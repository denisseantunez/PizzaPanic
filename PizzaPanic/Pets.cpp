
#include "Pets.h"
#include <cmath>

using std::pow;


/*******************************************************************************************************************************************************************/

void Pet::setHitbox(const float x, const float y)
{
	hitbox.setPosition(x, y);
	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(6.f);
}

/*******************************************************************************************************************************************************************/

void Pet::animate(float xPlayer, float yPlayer, float initialX, float initialY)
{
	float petAngle = this->petAngle(xPlayer, yPlayer, hitbox.getPosition().x, hitbox.getPosition().y, initialX, initialY);

	if ((petAngle >= 70 && petAngle <= 110) || (petAngle >= -290 && petAngle <= -250)) { // ARRIBA
		texRect.top = 498;
		if (texRect.left == 572)
			texRect.left = 468;
		else
			texRect.left += 52;
	}
	else if (petAngle > 110 && petAngle < 250) { // DERECHA
		texRect.top = 429;
		if (texRect.left == 572)
			texRect.left = 468;
		else
			texRect.left += 52;
	}
	else if ((petAngle >= 250 && petAngle <= 290) || (petAngle >= -110 && petAngle <= -70)) { // ABAJO
		texRect.top = 287;
		if (texRect.left == 572)
			texRect.left = 468;
		else
			texRect.left += 52;
	}
	else {
		if (petAngle > 0 || (petAngle > -250 && petAngle < -110)) { // IZQUIERDA
			texRect.top = 358; // IZQUIERDA
			if (texRect.left == 572)
				texRect.left = 468;
			else
				texRect.left += 52;
		}
		else {
			texRect.top = 429; // DERECHA
			if (texRect.left == 572)
				texRect.left = 468;
			else
				texRect.left += 52;
		}
	}
	sprite.setTextureRect(texRect);
}

/*******************************************************************************************************************************************************************/

void Pet::animate(float xPlayer, float yPlayer, float chiwisSpeed) 
{
	float chiwisAngle = this->chiwisAngle(xPlayer, yPlayer, hitbox.getPosition().x, hitbox.getPosition().y, chiwisSpeed);

	if ((chiwisAngle >= 70 && chiwisAngle <= 110) || (chiwisAngle >= -290 && chiwisAngle <= -250)) { // ARRIBA
		texRect.top = 498;
		if (texRect.left == 104)
			texRect.left = 0;
		else
			texRect.left += 52;
	}
	else if (chiwisAngle > 110 && chiwisAngle < 250) { // DERECHA
		texRect.top = 429;
		if (texRect.left == 104)
			texRect.left = 0;
		else
			texRect.left += 52;
	}
	else if ((chiwisAngle >= 250 && chiwisAngle <= 290) || (chiwisAngle >= -110 && chiwisAngle <= -70)) { // ABAJO
		texRect.top = 287;
		if (texRect.left == 104)
			texRect.left = 0;
		else
			texRect.left += 52;
	}
	else {
		if (chiwisAngle > 0 || (chiwisAngle > -250 && chiwisAngle < -110)) { // IZQUIERDA
			texRect.top = 358; // IZQUIERDA
			if (texRect.left == 104)
				texRect.left = 0;
			else
				texRect.left += 52;
		}
		else {
			texRect.top = 429; // DERECHA
			if (texRect.left == 104)
				texRect.left = 0;
			else
				texRect.left += 52;
		}
	}
	sprite.setTextureRect(texRect);
}

/*******************************************************************************************************************************************************************/

void Pet::followPlayer(float xPlayer, float yPlayer, float initialX, float initialY, sf::Time deltaTime)
{
	float xPet = hitbox.getPosition().x;
	float yPet = hitbox.getPosition().y;

	float dx = xPlayer - xPet;
	float dy = yPlayer - yPet;
	float distance = sqrt(pow(dx, 2.f) + pow(dy, 2.f));

	float dxaux = initialX - xPet;
	float dyaux = initialY - yPet;
	float distanceaux = sqrt(pow(dxaux, 2.f) + pow(dyaux, 2.f));

	sf::Vector2f unitVector(dx / distance, dy / distance);
	sf::Vector2f unitVectoraux(dxaux / (distanceaux + 0.1), dyaux / (distanceaux + 0.1));
	
	sf::Vector2f velocity = unitVector * (speed);
	sf::Vector2f velocityaux = unitVectoraux * (speed);

	if (distance <= RadioDetected && distanceaux <= RadioDetected)
		hitbox.move(velocity * deltaTime.asSeconds());
	else 
		hitbox.move(velocityaux * deltaTime.asSeconds());
}

/*******************************************************************************************************************************************************************/

void Pet::followPlayer(sf::Sprite mPlayer, const float chiwisRadio, float chiwisSpeed, sf::Time deltaTime)
{
	float dxchiwis = mPlayer.getPosition().x - hitbox.getPosition().x;
	float dychiwis = mPlayer.getPosition().y - hitbox.getPosition().y;
	float distancechiwis = sqrt(pow(dxchiwis, 2.f) + pow(dychiwis, 2.f));

	sf::Vector2f unitVectorchiwis(dxchiwis / distancechiwis, dychiwis / distancechiwis);
	if (distancechiwis <= chiwisRadio) {
		chiwisSpeed = 250.f;
		sf::Vector2f velocitychiwis = unitVectorchiwis * (chiwisSpeed);
		hitbox.move(velocitychiwis * deltaTime.asSeconds());
	}
	else {
		chiwisSpeed = 250.f;
		sf::Vector2f velocitychiwis = unitVectorchiwis * (chiwisSpeed);
		hitbox.move(velocitychiwis * deltaTime.asSeconds());
	}
}

/*******************************************************************************************************************************************************************/

void Pet::checkBites(float& mordidas, float& quitarVida, int PizzasEntregadas, sf::FloatRect playerCollider)
{
	sf::FloatRect petCollider = hitbox.getGlobalBounds();

	if (petCollider.intersects(playerCollider)) {
		mordidas += 0.5f + (PizzasEntregadas / 10.f);
		if (mordidas > 0 && mordidas < 120)
			quitarVida += 0.5f + (PizzasEntregadas / 10.f);
	}
}

/*******************************************************************************************************************************************************************/

void Pet::checkCollisions(const TileMap& objects, sf::Time deltaTime, const float petSpeed)
{
	for (const sf::FloatRect& collidable : objects.collidables) {
	
			// Handle collision
			sf::FloatRect intersection;
			if (hitbox.getGlobalBounds().intersects(collidable, intersection)) {
				// Calculate shortest distance to move hitbox away from intersection
				sf::Vector2f direction = hitbox.getPosition() - sf::Vector2f(intersection.left + intersection.width / 2, intersection.top + intersection.height / 2);
				float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= distance;
				sf::Vector2f size = hitbox.getSize();
				float radius = sqrt(size.x * size.x + size.y * size.y) / 2.f;
		
				// Calculate distance to move enemy away from intersection point
				float overlapX = (radius - (intersection.width / 2.f)) * direction.x;
				float overlapY = (radius - (intersection.height / 2.f)) * direction.y;
		
				// Add randomness to new position calculation
				sf::Vector2f randOffset = sf::Vector2f(((rand() % 51) - 25) * 0.2f, ((rand() % 51) - 25) * 0.2f);
				sf::Vector2f newPosition = hitbox.getPosition() + sf::Vector2f(overlapX, overlapY) + randOffset;
		
				// Adjust speed based on distance to collision point
				float speedAux = petSpeed * (distance / radius);
				sf::Vector2f velocity = direction * speedAux;
				hitbox.move(velocity * deltaTime.asSeconds());
				break;
			}
		}
}

/*******************************************************************************************************************************************************************/

float Pet::petAngle(float xPlayer, float yPlayer, float xPet, float yPet, float initialX, float initialY) {
	float dx = xPlayer - xPet;
	float dy = yPlayer - yPet;
	float distance = sqrt(pow(dx, 2.f) + pow(dy, 2.f));

	float dxaux = initialX - xPet;
	float dyaux = initialY - yPet;
	float distanceaux = sqrt(pow(dxaux, 2.f) + pow(dyaux, 2.f));

	sf::Vector2f unitVector(dx / distance, dy / distance);
	sf::Vector2f unitVectoraux(dxaux / (distanceaux + 0.1), dyaux / (distanceaux + 0.1));

	sf::Vector2f velocity = unitVector * (speed);
	sf::Vector2f velocityaux = unitVectoraux * (speed);

	if (distance <= RadioDetected && distanceaux <= RadioDetected) {
		float angle = atan2(velocity.y, velocity.x) * 180 / 3.141592 + 180.f;
		return angle;
	}
	else {
		float angle = atan2(velocityaux.y, velocityaux.x) * 180 / 3.141592 + 180.f;
		return angle;
	}
}

/*******************************************************************************************************************************************************************/

float Pet::chiwisAngle(float xPlayer, float yPlayer, float xPet, float yPet, const float chiwisSpeed) {
	float dx = xPlayer - xPet;
	float dy = yPlayer - yPet;
	float distance = sqrt(pow(dx, 2.f) + pow(dy, 2.f));
	sf::Vector2f unitVector(dx / distance, dy / distance);
	sf::Vector2f velocity = unitVector * (chiwisSpeed);
	float angle = atan2(velocity.y, velocity.x) * 180 / 3.141592 + 180.f;
	return angle;

}

/*******************************************************************************************************************************************************************/
