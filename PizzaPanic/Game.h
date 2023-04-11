#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "TileMap.h"
#include "SurfaceObjects.h"
#include "Collidable.h"
#include "MainMenu.h"

#define TimePerFrame sf::seconds(1.f / 60.f)

const float PlayerSpeed = 250.f;
const float SheguisSpeed = 250.f;
const float SoruyaSpeed = 150.f;
const float ChiwisSpeed = 200.f;
const float MindySpeed = 250.f;

using std::cout;


class Game
{
public:
	Game();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	bool mIsMovingUp = false;
	bool mIsMovingDown = false;
	bool mIsMovingLeft = false;
	bool mIsMovingRight = false;
	void run();


private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void HitBoxPlayer();
	void HitBoxChiwis();
	void HitBoxSheguis();
	void HitBoxSoruya();
	void HitBoxMindy();

	
private:
	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Sprite mPlayer;
	sf::View pView;
	sf::Music music;

	// Main menu
	MainMenu m_mainMenu;

	// Tilemaps
	TileMap background;
	SurfaceObjects objects;

	// Collision
	Collidable playerCollidable;
	Collidable chiwisCollidable;
	sf::Vector2f previousPlayerPos;

	// Game objects
	sf::RectangleShape hitboxplayer;
	sf::RectangleShape hitboxchiwis;
	sf::RectangleShape hitboxsheguis;
	sf::RectangleShape hitboxsoruya;
	sf::RectangleShape hitboxmindy;

};
