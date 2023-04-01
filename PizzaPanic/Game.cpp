
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

using std::cout;

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "SFML Application")
	, mTexture()
	, mPlayer()
	, iTexture()
	, iBackground()
{
	if (!mTexture.loadFromFile("C:\\Dev\\SFMLTest\\SFMLTest\\Images\\robot-idle.gif"))
	{
		// Handle loading error
		cout << ("Error al cargar el archivo.");
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(500.f, 500.f);
	mPlayer.setScale(.4, .4);

	if (!iTexture.loadFromFile("C:\\Dev\\SFMLTest\\SFMLTest\\Images\\grass.png"))
	{
		// Handle loading error
		cout << ("Error al cargar el fondo.");
	}

	iBackground.setTexture(iTexture);
	iBackground.setPosition(0.f, 0.f);
	iBackground.setScale(3, 3);

	//Custom View
	sf::View pView(sf::FloatRect(0, 0, mWindow.getSize().x, mWindow.getSize().y));



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
// Actualiza lo que pasa en el juego
{
	sf::Vector2f movement(0.f, 0.f);
	const float PlayerSpeed = 200.f;
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	pView.setCenter(mPlayer.getPosition());
	//pView.setSize(270.f, 270.f);
	mWindow.setView(pView);

	mPlayer.move(movement * deltaTime.asSeconds());
}
void Game::render()
// Representar gráficamente
{
	mWindow.clear();
	mWindow.draw(iBackground);
	mWindow.draw(mPlayer);
	mWindow.display();
}