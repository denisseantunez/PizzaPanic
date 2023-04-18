#pragma once

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "TileMap.h"
#include "SurfaceObjects.h"
#include "Collidable.h"
#include "MainMenu.h"

#define TimePerFrame sf::seconds(1.f / 60.f)

const float PlayerSpeed = 450.f;
const float SheguisSpeed = 250.f;
const float SoruyaSpeed = 150.f;
const float ChiwisSpeed = 200.f;
const float MindySpeed = 250.f;
const float RadioDetected = 300.f;


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
	void showMainMenu();
	void run();
    bool displayItemPrompt;
	
	


private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void HitBoxPlayer();
	void HitBoxChiwis();
	void HitBoxSheguis();
	void HitBoxSoruya();
	void HitBoxMindy();
	void Seguir(float xP, float yP, float xM, float yM, float Pox, float Poy, float Speed, sf::RectangleShape hitboxmascota, sf::Time deltaTime);
    sf::Keyboard::Key teclaItem = sf::Keyboard::Space;


private:
	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Sprite mPlayer;
	sf::View pView;
	sf::Music music;

    // Item
    sf::Texture mItemTexture;
    sf::Sprite mItem;
    sf::FloatRect mPlayerCollider;
    sf::FloatRect mItemCollider;
    sf::Text prompt;

    // Main menu
	MainMenu mainMenu;
	sf::Font m_font;
    sf::Font m_font2;
	sf::Texture m_menuBackground;

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