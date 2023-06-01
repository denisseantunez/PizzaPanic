#pragma once

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "TileMap.h"
#include "MainMenu.h"
#include "Pets.h"
#include "Player.h"

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
	void showMainMenu();
	void run();
	void MakeArray();
    bool displayItemPrompt;
	bool cargandoItem;
    int PosicionesItem[Filas][Columnas];
    int NuevaPosicion;
    int AlturaInicial = 2645;
    int deliveredPizzas = 0;
	float quitarVida = 0.0f;
	float bites = 0.f;
	float xPlayer;
    float yPlayer;
	sf::Vector2f EntregarPizza;

	float chiwisSpeed = 250.f;
	

private:
	// Funciones
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void Arrow(float xPlayer, float yPlayer, float xItem, float yItem);
	void ContadorPizzas(float xPlayer, float yPlayer, int cantidad_pizzas, sf::Text& texto, sf::Font& fuente);

	sf::Keyboard::Key teclaItem = sf::Keyboard::Space;
	sf::Vector2f movement;

	//Creating pets and Player
	Player Player;
	Pet chiwis;
	Pet sheguis;
	Pet soruya;
	Pet mindy;
	Pet bella;
	Pet manteca;
	Pet pushi;
	Pet muneca;

	// texto
	sf::Text texto;
	sf::Font fuente;
	sf::RectangleShape fondotexto;

	// Variables
	sf::RenderWindow mWindow;

	// Time
	sf::Clock clock;

	// Pizza logo in restaurant
	sf::Texture PizzaLogoTex;
	sf::Sprite PizzaLogo;

	// Game Over
	sf::Texture GameOverTex;
	sf::Sprite GameOver;

	// Camera
	sf::View pView;

	// Camera boundaries
	float camLeftBound = 510.f;
	float camRightBound = 2850.f;
	float camUpperBound = 510.f;
	float camLowerBound = 2850.f;

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
	TileMap objects;

	// Previous Positions
	sf::Vector2f previousChiwisPos;
	sf::Vector2f previousSheguisPos;
	sf::Vector2f previousSoruyaPos;
	sf::Vector2f previousMindyPos;

	// Game objects
	sf::ConvexShape arrow;

	void Initialize();
};