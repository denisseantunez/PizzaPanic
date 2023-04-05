// basado en el libro SFML Game Development :)

#include <iostream>
#include <cmath>
#include "Game.h"
//#include "TileMap.h"


using std::cout;


#define TimePerFrame sf::seconds(1.f / 60.f)


Game::Game()
	: mWindow(sf::VideoMode(800, 600), "Pizza Panic")
	, mTexture()
	, mPlayer()
	, pView(sf::FloatRect(0.f, 0.f, mWindow.getSize().x, mWindow.getSize().y))
{
	// Player
	if (!mTexture.loadFromFile("C:\\Users\\Manuel\\Pictures\\Images\\robot-idle.gif"))
	{
		// Handle loading error
		cout << ("Error al cargar el archivo.");
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(700.f, 700.f);
	mPlayer.setScale(0.3f, 0.3f);
	this->HitBoxPlayer();
	this->ChiwisMove();

	// Tilemap
	if (!background.load("C:\\Users\\Manuel\\Pictures\\Images\\Background.png", sf::Vector2u(48, 48), level, 70, 70))
	{
		// Handle loading error
		cout << ("Error al cargar el mapa.");
	}

	// Houses, trees, ...
	if (!objects.load("C:\\Users\\Manuel\\Pictures\\Images\\Objects.png", sf::Vector2u(48, 48), objectDisplay, 70, 70))
	{
		// Handle loading error
		cout << ("Error al cargar los objetos del mapa.");
	}

	// Music
	if (!music.openFromFile("C:\\Users\\Manuel\\Music\\Audios")) // canci�n de prueba nom�s
	{
		// Handle loading error
		cout << ("Error al cargar el audio.");
	}
	music.play();
	music.setVolume(20.f);

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
// User input
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}

void Game::update(sf::Time deltaTime)
// Update what happens in game
{
	sf::Vector2f movement(0.f, 0.f);
	const float PlayerSpeed = 250.f;
	const float ChiwisSpeed = 150.f;

	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	// Camera follows player
	pView.setCenter(mPlayer.getPosition());
	//pView.setSize(900.f, 900.f);
	pView.setSize(1300.f, 1300.f);
	mWindow.setView(pView);

	// Calculate the distance between the enemy and the player
	float dx = mPlayer.getPosition().x - chiwis.getPosition().x;
	float dy = mPlayer.getPosition().y - chiwis.getPosition().y;
	float distance = sqrt(pow(dx,2) + pow(dy,2));

	// Calculate the unit vector from the enemy to the player
	sf::Vector2f unitVector(dx / distance, dy / distance);

	// Calculate the velocity vector
	sf::Vector2f velocity = unitVector * ChiwisSpeed;

	mPlayer.move(movement * deltaTime.asSeconds());
	hitboxplayer.move(movement * deltaTime.asSeconds());
	chiwis.move(velocity * deltaTime.asSeconds());
}

void Game::HitBoxPlayer()
{
	this->hitboxplayer.setPosition(720.f, 725.f);
	this->hitboxplayer.setSize(sf::Vector2f(55.f, 75.f));
	this->hitboxplayer.setFillColor(sf::Color::Transparent);
	this->hitboxplayer.setOutlineColor(sf::Color::Red);
	this->hitboxplayer.setOutlineThickness(6.f);
}


void Game::ChiwisMove()
{
	this->chiwis.setPosition(500.f, 500.f);
	this->chiwis.setSize(sf::Vector2f(55.f, 75.f));
	this->chiwis.setFillColor(sf::Color::Transparent);
	this->chiwis.setOutlineColor(sf::Color::Cyan);
	this->chiwis.setOutlineThickness(6.f);
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(background);
	mWindow.draw(objects);
	mWindow.draw(mPlayer);
	mWindow.draw(hitboxplayer);
	mWindow.draw(chiwis);
	mWindow.display();

}

