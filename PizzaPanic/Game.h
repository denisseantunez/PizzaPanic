#pragma once

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "TileMap.h"
#include "SurfaceObjects.h"
#include "Collidable.h"
#include "MainMenu.h"
#include "Pets.h"

#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#define TimePerFrame sf::seconds(1.f / 60.f)
#define CantVida 60.f
#define chiwisRadio 100.f

const float PlayerSpeed = 450.f;
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
	float quitarVida = .0f;
	float mordidas = 0.f;
	float xPlayer;
    float yPlayer;
	sf::Vector2f EntregarPizza;

	float chiwisSpeed = 250.f;
	

private:
	// Funciones
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	void checkCollision(const SurfaceObjects& objects, const Collidable& petCollidable, sf::RectangleShape& petHitbox, const float petSpeed, sf::Time deltaTime);

	void HitBoxPlayer();

    sf::Keyboard::Key teclaItem = sf::Keyboard::Space;

	sf::Vector2f movement;

	Pet chiwis;
	Pet sheguis;
	Pet soruya;
	Pet mindy;
	Pet bella;
	Pet manteca;
	Pet pushi;
	Pet muneca;


	void BarraVida(float QuitarVida, float xPlayer, float yPlayer);
	void BarraVidaAux(float xPlayer, float yPlayer);
	
	void Flecha(float xPlayer, float yPlayer, float xItem, float yItem);

	void ContadorPizzas(float xPlayer, float yPlayer, int cantidad_pizzas, sf::Text& texto, sf::Font& fuente);

	// texto
	sf::Text texto;
	sf::Font fuente;
	sf::RectangleShape fondotexto;

	// Variables
	sf::RenderWindow mWindow;

	// Textures
	sf::Texture mTexture;

	// Texture Rects
	sf::IntRect m_playerRect;

	// Time
	sf::Clock clock;

	// Sprites
	sf::Sprite mPlayer;

	// Pizza logo in restaurant
	sf::Texture PizzaLogoTex;
	sf::Sprite PizzaLogo;

	// Game Over
	sf::Texture GameOverTex;
	sf::Sprite GameOver;

	// Camera
	sf::View pView;

	// Audio
	sf::Music music;
	sf::Music menuMusic;
	sf::Music deathSound;

    // Item
    sf::Texture mItemTexture;
	sf::Texture mItemArrowTexture;
	sf::Sprite mItemArrow;
    sf::Sprite mItem;
    sf::FloatRect mPlayerCollider;
    sf::FloatRect mItemCollider;
    sf::FloatRect mItemArrowCollider;
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
	sf::RectangleShape vida;
	sf::RectangleShape vidaaux;
	sf::ConvexShape arrow;

	void Initialize();

	
};