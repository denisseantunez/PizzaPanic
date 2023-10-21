
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*******************************************************************************************************************************************************************/

Game::Game()
	: mWindow(sf::VideoMode(800, 600), "Pizza Panic")
	, mainMenu(m_font, m_menuBackground)
{
	Initialize();
}

/*******************************************************************************************************************************************************************/

void Game::showMainMenu()
{
	while (mWindow.isOpen()){
		sf::Event event;
		while (mWindow.pollEvent(event)){
			mainMenu.handleEvent(event);
			if (event.type == sf::Event::Closed)
				mWindow.close();
		}
		mWindow.clear();
		mWindow.draw(mainMenu);
		mWindow.display();

		if (mainMenu.getSelectedOption() == MainMenu::Option::Jugar || mainMenu.getSelectedOption() == MainMenu::Option::Salir)
			break;
	}
}

/*******************************************************************************************************************************************************************/

void Game::processEvents()
// User input
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			player.handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			player.handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
    default:
      break;
		}
	}
}

/*******************************************************************************************************************************************************************/

void Game::update(sf::Time deltaTime)
// Update what happens in game
{
	// Saving player's coordinates on variables
	xPlayer = player.sprite.getPosition().x;
	yPlayer = player.sprite.getPosition().y;

	//cout << "x: " << xPlayer << std::endl;
	//cout << "y: " << yPlayer << std::endl;

	// Sprite Animations 
	if (clock.getElapsedTime().asSeconds() > 0.1f) {
		player.animate();

		pets[0].animate(xPlayer, yPlayer, chiwisSpeed);
		pets[1].animate(xPlayer, yPlayer, 407.536f, 2372.47f);
		pets[2].animate(xPlayer, yPlayer, 407.536f, 1240.f);
		pets[3].animate(xPlayer, yPlayer, 407.536f, 317.541f);
		pets[4].animate(xPlayer, yPlayer, 2264.14f, 1248.04f);
		pets[5].animate(xPlayer, yPlayer, 2264.14f, 2335.5f);
		pets[6].animate(yPlayer, yPlayer, 2378.68f, 228.298f);
		pets[7].animate(xPlayer, yPlayer, 1338.86f, 618.972f);

		clock.restart();
	}
	
	if (clock3.getElapsedTime().asSeconds() > 0.4f) {
		// Update day and night colors
		layer0.updateDayNightCycle(clock2);
		layer1.updateDayNightCycle(clock2);
		layer2.updateDayNightCycle(clock2);

		clock3.restart();
	}

	// Camera size
	mView.setSize(1000.f, 1000.f);

	// Camera follows player, if player is in the limits of the map, the camera locks 
	// in place to the corresponding boundary (camera boundaires)
	SetCameraView();

	mWindow.setView(mView);

	// Update item and player collision boundaries 
	mItemCollider = mItem.getGlobalBounds();
	mItemArrowCollider = mItemArrow.getGlobalBounds();
	mPlayerCollider = player.sprite.getGlobalBounds();

	// Sprites with hitboxes
	for (int i = 0; i < 8; ++i)
		pets[i].sprite.setPosition(pets[i].hitbox.getPosition().x, pets[i].hitbox.getPosition().y);

	// Check item collision
	CheckItemCollision();

	// Arrow 
	if (mItem.getPosition().x == 1436.f && mItem.getPosition().y == 1388.f)
		Arrow(xPlayer, yPlayer, mItem.getPosition().x, mItem.getPosition().y);
	else 
		Arrow(xPlayer, yPlayer, mItemArrow.getPosition().x, mItemArrow.getPosition().y);
	
	// Print text of pizzas
	this->ContadorPizzas(deliveredPizzas, text, m_font2);

	// Check if pet attacks player
	for (int i = 0; i < 8; ++i)
		pets[i].checkBites(bites, quitarVida, deliveredPizzas, mPlayerCollider);


	// Pets follow player
	//pets[0].followPlayer(player.sprite, chiwisRadio, chiwisSpeed, deltaTime);
	pets[1].followPlayer(xPlayer, yPlayer, 407.536f, 2372.47f, deltaTime);
	pets[2].followPlayer(xPlayer, yPlayer, 407.536f, 1240.f, deltaTime);
	pets[3].followPlayer(xPlayer, yPlayer, 407.536f, 317.541f, deltaTime);
	pets[4].followPlayer(xPlayer, yPlayer, 2264.14f, 1248.04f, deltaTime);
	pets[5].followPlayer(xPlayer, yPlayer, 2264.14f, 2335.5f, deltaTime);
	pets[6].followPlayer(xPlayer, yPlayer, 2378.68f, 228.298f, deltaTime);
	pets[7].followPlayer(xPlayer, yPlayer, 1338.86f, 618.972f, deltaTime);

	// Check for collisions
	player.checkCollisions(layer1);
	pets[0].checkCollisions(layer1, deltaTime, chiwisSpeed);

	for (int i = 1; i < 8; ++i)
		pets[i].checkCollisions(layer1, deltaTime, 250.f);

	//Move Player
	player.move(deltaTime);

	//Player's life
	this->player.PlayerLife(quitarVida, xPlayer, yPlayer);
	this->player.PlayerLifeAux(xPlayer, yPlayer);
}

/*******************************************************************************************************************************************************************/

void Game::render()
{
	mWindow.clear();;
	mWindow.draw(layer0);
	//mWindow.draw(layer1);
	mWindow.draw(layer2);
    mWindow.draw(mItem);
	
	mWindow.draw(player.sprite);
	mWindow.draw(layer1);
	mWindow.draw(pizzaLogo);
	//mWindow.draw(layer2);

	//mWindow.draw(player.sprite);
	
	mWindow.draw(mItemArrow);

	if (displayItemPrompt)
		mWindow.draw(prompt);
	
	mWindow.draw(player.playerLifeAux);
	mWindow.draw(player.playerLife);
	
	for (int i = 0; i < 8; ++i)
		mWindow.draw(pets[i].sprite);

	mWindow.draw(arrow);
	mWindow.draw(textBackground);
	mWindow.draw(text);

	mWindow.display();

}

/*******************************************************************************************************************************************************************/

void Game::Initialize()
{
	// Initialize MainMenu 
	if (!m_font.loadFromFile("Fonts/ka1.ttf"))
		cout << ("Error al cargar el font.");
	
	if (!m_font2.loadFromFile("Fonts/font2.ttf"))
		cout << ("Error al cargar el font del item.");
	
	if (!m_menuBackground.loadFromFile("Images/FondoMainMenu.png"))
		cout << ("Error al cargar el fondo del menu.");
	MainMenu mainMenu(m_font, m_menuBackground);

	// View
	mView = sf::View(sf::FloatRect(0.f, 0.f, mWindow.getSize().x, mWindow.getSize().y));

	// Item
	if (!mItemTexture.loadFromFile("Images/PizzaBox.png"))
		cout << ("Error al cargar el archivo del Item.");
	mItem.setTexture(mItemTexture);
	mItem.setPosition(3070.f, 2760.f);
	mItem.setScale(1.7f, 1.7f);

	// Arrow's item
	if (!mItemArrowTexture.loadFromFile("Images/PixelArrowRotated.png"))
		cout << ("Error al cargar el archivo del Item.");
	mItemArrow.setTexture(mItemArrowTexture);
	mItemArrow.setPosition(-1000, -1000);
	mItemArrow.setScale(0.3f, 0.3f);

	// Game Over
	if (!GameOverTex.loadFromFile("Images/GameOver_.png"))
		cout << ("Error al cargar el archivo de game over.");
	gameOver.setTexture(GameOverTex);
	gameOver.setScale(1.5f, 1.5f);

	// Music 
	if (!music.openFromFile("Audios/GORILLAvsHUMAN.wav"))
		cout << ("Error al cargar el audio.");
	music.setVolume(10.f);

	if (!menuMusic.openFromFile("Audios/omairi.wav"))
		cout << ("Error al cargar el audio del menu.");
	menuMusic.setVolume(20.f);

	if (!deathSound.openFromFile("Audios/death.wav"))
		cout << ("Error al cargar el audio de game over.");

	// Tilemap 
	if (!layer0.load("Images/Tileset.png", sf::Vector2u(48, 48), 0))
		cout << ("Error al cargar el mapa.");
	if (!layer1.load("Images/Tileset.png", sf::Vector2u(48, 48), 1))
		cout << ("Error al cargar los objetos del mapa.");
	if (!layer2.load("Images/Tileset.png", sf::Vector2u(48, 48), 2))
		cout << ("Error al cargar los detalles del mapa.");

	// Pizza logo in restaurant
	if (!PizzaLogoTex.loadFromFile("Images/Pizza.png"))
		cout << ("Error al cargar el archivo de la pizza");
	pizzaLogo.setTexture(PizzaLogoTex);
	pizzaLogo.setScale(0.1, 0.1);
	pizzaLogo.setPosition(1315.f, 1167.f);

	// Player 
	if (!player.texture.loadFromFile("Images/Robot.png"))
		cout << ("Error al cargar el archivo.");
	player.texRect.left = 0;
	player.texRect.top = 0;
	player.texRect.width = 320;
	player.texRect.height = 320;
	player.sprite.setTexture(player.texture);
	player.sprite.setTextureRect(player.texRect);
	player.sprite.setPosition(2500.f, 2500.f);
	player.sprite.setScale(player.escaleX, player.escaleY);

	// Item's texture
	if (!mItemTexture.loadFromFile("Images/PizzaBox.png"))
		cout << ("Error al cargar el archivo del Item.");
	mItem.setTexture(mItemTexture);
	mItem.setPosition(1436.f, 1388.f);
	mItem.setScale(1.7f, 1.7f);

	if (!mItemArrowTexture.loadFromFile("Images/PixelArrowRotated.png"))
		cout << ("Error al cargar el archivo del Item.");
	mItemArrow.setTexture(mItemArrowTexture);
	//mItem.setPosition(-1000, -1000);

	// Create pets
	for (int i = 0; i < 8; ++i) {
		pets[i].texture.loadFromFile("Images/Mascotas.png");
		pets[i].texRect.width = 36;
		pets[i].texRect.height = 47;
		pets[i].sprite.setTexture(pets[i].texture);
		pets[i].sprite.setTextureRect(pets[i].texRect);
		pets[i].sprite.setScale(1.5f, 1.5f);
	}

	// [0] --> chiwis
	// [1] --> sheguis
	// [2] --> soruya
	// [3] --> mindy
	// [4] --> bella
	// [5] --> manteca
	// [6] --> pushi
	// [7] --> mu�eca

	pets[0].texRect.left = 0;
	pets[0].sprite.setPosition(1361.51f, 2678.98f);

	pets[1].texRect.left = 0;
	pets[1].sprite.setPosition(407.536f, 2372.47f);

	pets[2].texRect.left = 156;
	pets[2].sprite.setPosition(407.536f, 1240.f);

	pets[3].texRect.left = 156;
	pets[3].sprite.setPosition(407.536f, 317.541f);

	pets[4].texRect.left = 468;
	pets[4].sprite.setPosition(2264.14f, 1248.04f);

	pets[5].texRect.left = 312;
	pets[5].sprite.setPosition(2264.14f, 2335.5f);

	pets[6].texRect.left = 312;
	pets[6].sprite.setPosition(2378.68f, 228.298f);

	pets[7].texRect.left = 468;
	pets[7].sprite.setPosition(1338.86f, 618.972f);
	

	// Item's texture 
	prompt.setFont(m_font2);

	// Hitboxes 
	pets[0].setHitbox(1361.51f, 2678.98f);
	pets[1].setHitbox(407.536f, 2372.47f);
	pets[2].setHitbox(407.536f, 1240.f);
	pets[3].setHitbox(407.536f, 317.541f);
	pets[4].setHitbox(2264.14f, 1248.04f);
	pets[5].setHitbox(2264.14f, 2335.5f);
	pets[6].setHitbox(2378.68f, 228.298f);
	pets[7].setHitbox(1338.86f, 618.972f);

	// Creating array and seed
	MakeArray();
	srand(time(NULL));
}

/*******************************************************************************************************************************************************************/

void Game::ContadorPizzas(int cantidad_pizzas, sf::Text& texto, sf::Font& fuente) {

	this->textBackground.setPosition(mView.getCenter().x - 450.f, mView.getCenter().y - 450.f);
	this->textBackground.setSize(sf::Vector2f(260.f, 30.f));
	this->textBackground.setFillColor(sf::Color::Blue);
	this->textBackground.setOutlineColor(sf::Color::Black);
	this->textBackground.setOutlineThickness(4.f);
	this->text.setFont(fuente); // "fuente" is the object of the font you want to use.
	this->text.setCharacterSize(20); // adjust the size of the text for our neccesities.
	this->text.setPosition(mView.getCenter().x - 450.f, mView.getCenter().y - 450.f);
	this->text.setString("Pizzas entregadas: " + std::to_string(cantidad_pizzas));
}

/*******************************************************************************************************************************************************************/

void Game::Arrow(float xPlayer, float yPlayer, float xItem, float yItem) {

	float dx = xItem - xPlayer;
	float dy = yItem - yPlayer;
	float angle = atan2(dy, dx) * 180 / 3.141592 - 90; 
	this->arrow.setRotation(angle); 
	float arrowOffset = -50.f; 

	this->arrow.setPointCount(3);
	this->arrow.setPoint(0, sf::Vector2f(xPlayer, yPlayer));
	this->arrow.setPoint(1, sf::Vector2f(xPlayer - 10.f, yPlayer - 10.f));
	this->arrow.setPoint(2, sf::Vector2f(xPlayer + 10.f, yPlayer - 10.f));
	this->arrow.setFillColor(sf::Color::Yellow);
	this->arrow.setOrigin(xPlayer, yPlayer - 20.f);
	this->arrow.setScale(1.f,1.f); 
	this->arrow.setOutlineThickness(2.f);
	this->arrow.setOutlineColor(sf::Color::Black);

	float circleRadius = 80.f; 
	sf::Vector2f circleCenter(xPlayer + 15.f, yPlayer + 20.f);

	float angleRadians = (angle + 90) * 3.141592 / 180; 
	sf::Vector2f arrowPosition(cos(angleRadians) * circleRadius, sin(angleRadians) * circleRadius);

	arrowPosition += circleCenter;

	this->arrow.setPosition(arrowPosition.x, arrowPosition.y);
}

/*******************************************************************************************************************************************************************/

void Game::CheckItemCollision() {
	displayItemPrompt = false;
	if (mPlayerCollider.intersects(mItemCollider) || mPlayerCollider.intersects(mItemArrowCollider)) {

		if (mItem.getPosition().x == 1436.f && mItem.getPosition().y == 1388.f) {
			prompt.setString("Presiona espacio para recoger la pizza!");
		}
		else {
			prompt.setString("Presiona espacio para dejar la pizza!");
		}
		displayItemPrompt = true;
		if (cargandoItem) {
			prompt.setPosition(mItemArrow.getPosition().x - 300, mItemArrow.getPosition().y + 100);
		}
		else {
			prompt.setPosition(mItem.getPosition().x - 300, mItem.getPosition().y + 100);
		}

		if (sf::Keyboard::isKeyPressed(teclaItem)) {
			if (cargandoItem) {
				quitarVida = 0.f;
				bites = 0.f;
				mItemArrow.setPosition(-1000, -1000);
				mItem.setPosition(1436.f,1388.f); 
				mItem.setScale(1.7f, 1.7f);
				cargandoItem = false;
				deliveredPizzas++;
			}
			else {
				cargandoItem = true;
				NuevaPosicion = rand() % 22;
				mItemArrow.setPosition(PosicionesItem[0][NuevaPosicion], PosicionesItem[1][NuevaPosicion]);
				mItemArrow.setScale(0.3f, 0.3f);
				mItem.setPosition(-1000, -1000);
			}
		}
	}
}

/*******************************************************************************************************************************************************************/

void Game::SetCameraView() {
	// Check corners only
	if (xPlayer < camLeftBound && yPlayer < camUpperBound)
		mView.setCenter(camLeftBound, camUpperBound);
	else if (xPlayer > camRightBound && yPlayer < camUpperBound)
		mView.setCenter(camRightBound, camUpperBound);
	else if (xPlayer < camLeftBound && yPlayer > camLowerBound)
		mView.setCenter(camLeftBound, camLowerBound);
	else if (xPlayer > camRightBound && yPlayer > camLowerBound)
		mView.setCenter(camRightBound, camLowerBound);

	// Check sides only
	else if (xPlayer < camLeftBound)
		mView.setCenter(camLeftBound, yPlayer);
	else if (xPlayer > camRightBound)
		mView.setCenter(camRightBound, yPlayer);
	else if (yPlayer > camLowerBound)
		mView.setCenter(xPlayer, camLowerBound);
	else if (yPlayer < camUpperBound)
		mView.setCenter(xPlayer, camUpperBound);
	else
		mView.setCenter(xPlayer, yPlayer);
}

/*******************************************************************************************************************************************************************/




