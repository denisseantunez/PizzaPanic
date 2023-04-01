
#include <iostream>

#include "Game.h"


using std::cout;


Game::Game()
	: mWindow(sf::VideoMode(800, 600), "Pizza Panic")
	, mTexture()
	, mPlayer()
	, iTexture()
	, iBackground()
	, pView(sf::FloatRect(0.f, 0.f, mWindow.getSize().x, mWindow.getSize().y))
{
	//Player
	if (!mTexture.loadFromFile("Images\\robot-idle.gif"))
	{
		// Handle loading error
		cout << ("Error al cargar el archivo.");
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(500.f, 500.f);
	mPlayer.setScale(0.4f, 0.4f);

	/*
	if (!iTexture.loadFromFile("grass.png"))
	{
		// Handle loading error
		cout << ("Error al cargar el fondo.");
	}

	iBackground.setTexture(iTexture);
	iBackground.setPosition(0.f, 0.f);
	iBackground.setScale(3, 3);
	*/

	//Music
	if (!music.openFromFile("C:\\Dev\\SFMLTest\\SFMLTest\\Audios\\CreepyForest.wav"))
	{
		// Handle loading error
		cout << ("Error al cargar el audio.");
	}
	music.play();

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
	pView.setSize(1300.f, 1300.f);
	mWindow.setView(pView);

	mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(iBackground);
	mWindow.draw(mPlayer);
	mWindow.display();
}