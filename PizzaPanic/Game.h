#pragma once

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "TileMap.h"
#include "SurfaceObjects.h"
#include "Collidable.h"
#include "MainMenu.h"

#include <cstdlib>
#include <ctime>

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
const int Filas = 2;
const int Columnas = 35;


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
	void MakeArray();
    bool displayItemPrompt;
	bool cargandoItem;
    int PosicionesItem[Filas][Columnas];
    int NuevaPosicion;
    int AlturaInicial = 2645;
    int PizzasEntregadas = 0;
	float QuitarVida = .0f;
	float Mordidas = 0.f;
	
	// chiwis temporal
    float ChiwisWidth;
    float ChiwisHeight;
	float SheguisWidth;
	float SheguisHeight;

	private:
	// Funciones
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
	
	// Variables
	sf::RenderWindow mWindow;

	// Textures
	sf::Texture mTexture;
	sf::Texture chiwisTexture;
	sf::Texture sheguisTexture;
	sf::Texture soruyaTexture;
	sf::Texture mindyTexture;
	sf::Texture bellaTexture;
	sf::Texture mantecaTexture;
	sf::Texture pushiTexture;
	sf::Texture munecaTexture;

	// Player
	sf::IntRect m_playerRect;

	// Time
	sf::Clock clock;

	// Sprites
	sf::Sprite mPlayer;
	sf::Sprite Chiwis;
	sf::Sprite Sheguis;
	sf::Sprite Soruya;
	sf::Sprite Mindy;
	sf::Sprite Bella;
	sf::Sprite Manteca;
	sf::Sprite Pushi;
	sf::Sprite Muneca;

	// Pizza logo in restaurant
	sf::Texture PizzaLogoTex;
	sf::Sprite PizzaLogo;

	// Camera
	sf::View pView;

	// Audio
	sf::Music music;
	sf::Music menuMusic;

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

	// Collision with player
	sf::FloatRect ChiwisCollider;

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
	sf::VertexArray triangle;

};