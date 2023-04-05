#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "TileMap.h"
#include "SurfaceObjects.h"

#define TimePerFrame sf::seconds(1.f / 60.f)

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
	void ChiwisMove();
	void HitBoxPlayer();

	
private:
	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Sprite mPlayer;
	sf::View pView;
	sf::Music music;
	TileMap background;
	SurfaceObjects objects;

	//Game objects
	sf::RectangleShape hitboxplayer;
	sf::RectangleShape chiwis;

};
