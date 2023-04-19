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
#define CantVida 60.f

const float PlayerSpeed = 450.f;
const float SheguisSpeed = 250.f;
const float SoruyaSpeed = 150.f;
const float ChiwisSpeed = 300.f;
const float MindySpeed = 250.f;
const float BellaSpeed = 250.f;
const float MantecaSpeed = 250.f;
const float PushiSpeed = 250.f;
const float MunecaSpeed = 250.f;
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

    sf::Keyboard::Key teclaItem = sf::Keyboard::Space;

	void HitBoxBella();
	void HitBoxManteca();
	void HitBoxPushi();
	void HitBoxMuneca();
	void BarraVida(float QuitarVida, float xPlayer, float yPlayer);
	void BarraVidaAux(float xPlayer, float yPlayer);
	void Seguir(float xPlayer, float yPlayer, float xMascota, float yMascota, float Pox, float Poy, float Speed, sf::RectangleShape& hitboxmascota, sf::Time deltaTime);
	


private:
	sf::RenderWindow mWindow;

	// Textures
	sf::Texture mTexture;
	sf::Texture chiwisTexture;
	sf::Texture sheguisTexture;
	sf::Texture soruyaTexture;
	sf::Texture mindyTexture;

	// Sprites
	sf::Sprite mPlayer;
	sf::Sprite Chiwis;
	sf::Sprite Sheguis;
	sf::Sprite Soruya;
	sf::Sprite Mindy;

	// Camera
	sf::View pView;

	// Audio
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
	Collidable sheguisCollidable;
	Collidable soruyaCollidable;
	Collidable mindyCollidable;
	Collidable bellaCollidable;
	Collidable mantecaCollidable;
	Collidable pushiCollidable;
	Collidable munecaCollidable;

	// Previous Positions
	sf::Vector2f previousPlayerPos;
	sf::Vector2f previousChiwisPos;
	sf::Vector2f previousSheguisPos;
	sf::Vector2f previousSoruyaPos;
	sf::Vector2f previousMindyPos;

	// Game objects
	sf::RectangleShape hitboxplayer;
	sf::RectangleShape hitboxchiwis;
	sf::RectangleShape hitboxsheguis;
	sf::RectangleShape hitboxsoruya;
	sf::RectangleShape hitboxmindy;
	sf::RectangleShape hitboxbella;
	sf::RectangleShape hitboxmanteca;
	sf::RectangleShape hitboxpushi;
	sf::RectangleShape hitboxmuneca;
	sf::RectangleShape vida;
	sf::RectangleShape vidaaux;

};