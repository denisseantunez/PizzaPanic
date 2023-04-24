// basado en el libro SFML Game Development :)

#include "Game.h"

/*******************************************************************************************************************************************************************/

Game::Game()
	: mWindow(sf::VideoMode(800, 600), "Pizza Panic")
	, mTexture()
	, mPlayer()
	, pView(sf::FloatRect(0.f, 0.f, mWindow.getSize().x, mWindow.getSize().y))
	, mainMenu(m_font, m_menuBackground)
{

	//Initialize MainMenu ************************************************************************
	if (!m_font.loadFromFile("Fonts\\ka1.ttf"))
	{
		// Handle loading error
		cout << ("Error al cargar el font.");
	}
    if (!m_font2.loadFromFile("Fonts\\font2.ttf"))
    {
        // Handle loading error
        cout << ("Error al cargar el font del item.");
    }
	if (!m_menuBackground.loadFromFile("Images\\FondoMainMenu.png"))
	{
		// Handle loading error
		cout << ("Error al cargar el fondo del menu.");
	}
	MainMenu mainMenu(m_font, m_menuBackground);


	// Player ************************************************************************************
	if (!mTexture.loadFromFile("Images\\Robot.png"))
	{
		// Handle loading error
		cout << ("Error al cargar el archivo.");
	}
	m_playerRect.left = 0;
	m_playerRect.top = 0;
	m_playerRect.width = 320;
	m_playerRect.height = 320;
	mPlayer.setTexture(mTexture);
	mPlayer.setTextureRect(m_playerRect);
	mPlayer.setPosition(2500.f, 2500.f);
	mPlayer.setScale(0.18f, 0.18f);


    // Textura del Item *************************************************************************
    if (!mItemTexture.loadFromFile("Images\\PizzaBox.png"))
    {
        // Handle loading error
        cout << ("Error al cargar el archivo del Item.");
    }
    mItem.setTexture(mItemTexture);
    mItem.setPosition(3070.f, 2760.f);
    mItem.setScale(1.7f, 1.7f);

	// Textura Chiwis **************************************************************************
    if (!chiwisTexture.loadFromFile("Images\\Mascotas.png")){
        // Handle loading error
        cout << ("Error al cargar la textura de chiwis.");
    }
    Chiwis.setTexture(chiwisTexture);
	Chiwis.setTextureRect(sf::IntRect(0, 288, 48, 48));
    Chiwis.setPosition(3000.f, 700.f);

    sf::FloatRect ChiwisRect = Chiwis.getGlobalBounds();
    ChiwisWidth = ChiwisRect.width;
    ChiwisHeight = ChiwisRect.height;

	// Textura Sheguis **************************************************************************
	if (!sheguisTexture.loadFromFile("Images\\Mascotas.png")) {
		// Handle loading error
		cout << ("Error al cargar la textura de sheguis.");
	}
	Sheguis.setTexture(sheguisTexture);
	Sheguis.setTextureRect(sf::IntRect(480, 288, 48, 48));
	Sheguis.setPosition(2000.f, 2100.f);

	sf::FloatRect SheguisRect = Sheguis.getGlobalBounds();
	SheguisWidth = SheguisRect.width;
	SheguisHeight = SheguisRect.height;

    // Texto del item ***************************************************************************
    prompt.setFont(m_font2);
    prompt.setString("Presiona espacio para recoger el item!");

	// Hitboxes ********************************************************************************
	this->HitBoxPlayer();
	this->HitBoxChiwis();
	this->HitBoxSheguis();
	this->HitBoxSoruya();
	this->HitBoxMindy();
	this->HitBoxBella();
	this->HitBoxManteca();
	this->HitBoxPushi();
	this->HitBoxMuneca();

	// Tilemap *********************************************************************************
	if (!background.load("Images\\Tileset.png", sf::Vector2u(48, 48)))
	{
		// Handle loading error
		cout << ("Error al cargar el mapa.");
	}

	// Collision objects ***********************************************************************
	if (!objects.load("Images\\Tileset.png", sf::Vector2u(48, 48)))
	{
		// Handle loading error
		cout << ("Error al cargar los objetos del mapa.");
	}

	// Pizza logo in restaurant ****************************************************************
	if (!PizzaLogoTex.loadFromFile("Images\\Pizza.png"))
	{
		// Handle loading error
		cout << ("Error al cargar el archivo de la pizza");
	}
	PizzaLogo.setTexture(PizzaLogoTex);
	PizzaLogo.setPosition(2795.f, 2355.f);
	PizzaLogo.setScale(0.1f, 0.1f);

	// Ocean ***********************************************************************************
	if (!OceanTex.loadFromFile("Images\\Mar.png"))
	{
		// Handle loading error
		cout << ("Error al cargar el archivo del mar.");
	}
	Ocean.setTexture(OceanTex);
	Ocean.setPosition(-600.f, -300.f);

	// Game Over *******************************************************************************
	if (!GameOverTex.loadFromFile("Images\\GameOver_.png"))
	{
		// Handle loading error
		cout << ("Error al cargar el archivo de game over.");
	}
	GameOver.setTexture(GameOverTex);
	GameOver.setScale(1.5f, 1.5f);

	// Music ***********************************************************************************
	if (!music.openFromFile("Audios\\GORILLAvsHUMAN.wav")) 
	{
		// Handle loading error
		cout << ("Error al cargar el audio.");
	}
	music.setVolume(20.f);

	if (!menuMusic.openFromFile("Audios\\omairi.wav"))
	{
		// Handle loading error
		cout << ("Error al cargar el audio del menu.");
	}
	menuMusic.setVolume(20.f);

	if (!deathSound.openFromFile("Audios\\death.wav"))
	{
		// Handle loading error
		cout << ("Error al cargar el audio de game over.");
	}
	deathSound.setVolume(40.f);


	// Crear arreglo y empezar semilla **********************************************************
	MakeArray();
    srand(time(NULL));
}

/*******************************************************************************************************************************************************************/

void Game::showMainMenu()
{

	while (mWindow.isOpen())
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			mainMenu.handleEvent(event);
			if (event.type == sf::Event::Closed)
			{
				mWindow.close();
			}
		}

		mWindow.clear();
		mWindow.draw(mainMenu);
		mWindow.display();

		if (mainMenu.getSelectedOption() == MainMenu::Option::Jugar || mainMenu.getSelectedOption() == MainMenu::Option::Salir)
			break;
	}
}

/*******************************************************************************************************************************************************************/

void Game::run()
{
	do {
		mainMenu.resetSelectedOption();
		Mordidas = 0.f;
		QuitarVida = 0.f;
		mPlayer.setPosition(2500.f, 2500.f);
		pView.reset(sf::FloatRect(0, 0, mWindow.getSize().x, mWindow.getSize().y));
		mWindow.setView(pView);

		menuMusic.play();
		menuMusic.setLoop(true);

		showMainMenu();

		// If Play button is clicked, start the game
		if (mainMenu.getSelectedOption() == MainMenu::Option::Jugar) {

			// Play game music
			menuMusic.stop();
			music.play();
			music.setLoop(true);

			// Keep track of the player's initial position
			sf::Vector2f previousPlayerPos = mPlayer.getPosition();

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
				if (Mordidas == 120) {
					music.stop();
					deathSound.play();
					deathSound.setLoop(true);
					GameOver.setPosition(mPlayer.getPosition().x - 460.f, mPlayer.getPosition().y - 500.f);
					mWindow.clear();
					mWindow.draw(GameOver);
					mWindow.display();
					Sleep(1900);
					deathSound.stop();
					break;
				}
			}
		}
	} while (mainMenu.getSelectedOption() == MainMenu::Option::Jugar);

}

/*******************************************************************************************************************************************************************/

void Game::processEvents()
// User input
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mainMenu.handleEvent(event);
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

/*******************************************************************************************************************************************************************/

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
	{
		mIsMovingUp = isPressed;
	}
	else if (key == sf::Keyboard::S)
	{
		mIsMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::A)
	{
		mIsMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::D)
	{
		mIsMovingRight = isPressed;
	}

}

/*******************************************************************************************************************************************************************/

void Game::update(sf::Time deltaTime)
// Update what happens in game
{
	sf::Vector2f movement(0.f, 0.f);

	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	// Player Animation *****************************************************************************
	if (clock.getElapsedTime().asSeconds() > 0.1f) {
		if (m_playerRect.left == 1920)
			m_playerRect.left = 0;
		else { m_playerRect.left += 320; }
		mPlayer.setTextureRect(m_playerRect);
		clock.restart();
	}

	// Camera follows player ************************************************************************
	pView.setCenter(mPlayer.getPosition());
	pView.setSize(1000.f, 1000.f);
	mWindow.setView(pView);

	// Update item and player collision boundaries *************************************************
	mItemCollider = mItem.getGlobalBounds();
	mPlayerCollider = mPlayer.getGlobalBounds();
	ChiwisCollider = hitboxchiwis.getGlobalBounds();
	SheguisCollider = hitboxsheguis.getGlobalBounds();
	SoruyaCollider = hitboxsoruya.getGlobalBounds();
	MindyCollider = hitboxmindy.getGlobalBounds();
	MantecaCollider = hitboxmanteca.getGlobalBounds();
	MunecaCollider = hitboxmuneca.getGlobalBounds();
	PushiCollider = hitboxpushi.getGlobalBounds();
	BellaCollider = hitboxbella.getGlobalBounds();

	//Sprites junto con la hitbox.
    Chiwis.setPosition(hitboxchiwis.getPosition().x,hitboxchiwis.getPosition().y);

	// Check item collision ************************************************************************
	displayItemPrompt = false;
	if (mPlayerCollider.intersects(mItemCollider)) {

		displayItemPrompt = true;
		prompt.setPosition(mItem.getPosition().x - 300,mItem.getPosition().y + 100);

		if (sf::Keyboard::isKeyPressed(teclaItem)) {
			if(cargandoItem){
				QuitarVida = 0.f;
				Mordidas = 0.f;
                mItem.setPosition(3070.f, 2760.f);
                cargandoItem = false;
                ++PizzasEntregadas;
            } else {
                cargandoItem = true;
                NuevaPosicion = rand() % 35;
                mItem.setPosition(PosicionesItem[0][NuevaPosicion], PosicionesItem[1][NuevaPosicion]);
            }
		}
	}

	if (ChiwisCollider.intersects(mPlayerCollider) ||
		SheguisCollider.intersects(mPlayerCollider)||
		SoruyaCollider.intersects(mPlayerCollider) ||
		BellaCollider.intersects(mPlayerCollider)  ||
		PushiCollider.intersects(mPlayerCollider)  ||
		MunecaCollider.intersects(mPlayerCollider) ||
		MindyCollider.intersects(mPlayerCollider)  ||
		MantecaCollider.intersects(mPlayerCollider))
	{-
		Mordidas++;
		if (Mordidas > 0 && Mordidas < 120) 
			QuitarVida += 0.5f;
        displayItemPrompt = true;
        prompt.setPosition(Chiwis.getPosition().x - 300,Chiwis.getPosition().y + 100);
    }

	// Keep track of previous positions ************************************************************************
	sf::Vector2f previousPlayerPos = mPlayer.getPosition();
	sf::Vector2f previousChiwisPos = hitboxchiwis.getPosition();
	sf::Vector2f previousSheguisPos = hitboxsheguis.getPosition();
	sf::Vector2f previousSoruyaPos = hitboxsoruya.getPosition();
	sf::Vector2f previousMindyPos = hitboxmindy.getPosition();
	sf::Vector2f previousBellaPos = hitboxbella.getPosition();
	sf::Vector2f previousMantecaPos = hitboxmanteca.getPosition();
	sf::Vector2f previousPushiPos = hitboxpushi.getPosition();
	sf::Vector2f previousMunecaPos = hitboxmuneca.getPosition();

	// Guardar Coordenadas del jugador en variables*************************************************************
	float xPlayer = mPlayer.getPosition().x;
	float yPlayer = mPlayer.getPosition().y;

	//**************SHEGUIS*************************************************************************************

	float xSheguis = hitboxsheguis.getPosition().x;
	float ySheguis = hitboxsheguis.getPosition().y;
	Seguir(xPlayer, yPlayer, xSheguis, ySheguis, 2000, 2100, SheguisSpeed, hitboxsheguis, deltaTime);
	//********************************************************************************************************


	//**************SORUYA************************************************************************************

	float xSoruya = hitboxsoruya.getPosition().x;
	float ySoruya = hitboxsoruya.getPosition().y;
	Seguir(xPlayer, yPlayer, xSoruya, ySoruya, 3000, 700, SoruyaSpeed, hitboxsoruya, deltaTime);
	//*******************************************************************************************************


	//**************MINDY************************************************************************************

	float xMindy = hitboxmindy.getPosition().x;
	float yMindy = hitboxmindy.getPosition().y;
	Seguir(xPlayer, yPlayer, xMindy, yMindy, 1816, 1466, MindySpeed, hitboxmindy, deltaTime);
	//******************************************************************************************************


	//**************BELLA***********************************************************************************

	float xBella = hitboxbella.getPosition().x;
	float yBella = hitboxbella.getPosition().y;
	Seguir(xPlayer, yPlayer, xBella, yBella, 85, 790, BellaSpeed, hitboxbella, deltaTime);
	//*****************************************************************************************************


	//**************MANTECA********************************************************************************

	float xManteca = hitboxmanteca.getPosition().x;
	float yManteca = hitboxmanteca.getPosition().y;
	Seguir(xPlayer, yPlayer, xManteca, yManteca, 2366, 2800, MantecaSpeed, hitboxmanteca, deltaTime);
	//****************************************************************************************************


	//**************PUSHI*********************************************************************************

	float xPushi = hitboxpushi.getPosition().x;
	float yPushi = hitboxpushi.getPosition().y;
	Seguir(xPlayer, yPlayer, xPushi, yPushi, 85, 1950, PushiSpeed, hitboxpushi, deltaTime);

	//***************************************************************************************************


	//**************MUNECA*******************************************************************************

	float xMuneca = hitboxmuneca.getPosition().x;
	float yMuneca = hitboxmuneca.getPosition().y;
	Seguir(xPlayer, yPlayer, xMuneca, yMuneca, 1500, 2415, MunecaSpeed, hitboxmuneca, deltaTime);
	//**************************************************************************************************


	//*************CHIWIS******************************************************************************

	float dxchiwis = mPlayer.getPosition().x - hitboxchiwis.getPosition().x;
	float dychiwis = mPlayer.getPosition().y - hitboxchiwis.getPosition().y;
	float distancechiwis = sqrt(pow(dxchiwis, 2.f) + pow(dychiwis, 2.f));

	sf::Vector2f unitVectorchiwis(dxchiwis / distancechiwis, dychiwis / distancechiwis);
	if (distancechiwis <= RadioChiwis) {
		ChiwisSpeed = 300.f;
		sf::Vector2f velocitychiwis = unitVectorchiwis * (ChiwisSpeed);
		hitboxchiwis.move(velocitychiwis * deltaTime.asSeconds());
	}
	else {
		ChiwisSpeed = 400.f;
		sf::Vector2f velocitychiwis = unitVectorchiwis * (ChiwisSpeed);
		hitboxchiwis.move(velocitychiwis * deltaTime.asSeconds());
	}
	//*************************************************************************************************


	// Move player 
	mPlayer.move(movement * deltaTime.asSeconds());
	hitboxplayer.move(movement * deltaTime.asSeconds());



	// *************COLLISIONS*************************************************************************

	// Create Collidable object for the player and enemies
	Collidable playerCollidable(1, mPlayer.getGlobalBounds(), true);
	Collidable chiwisCollidable(1, hitboxchiwis.getGlobalBounds(), true);
	Collidable sheguisCollidable(1, hitboxsheguis.getGlobalBounds(), true);
	Collidable soruyaCollidable(1, hitboxsoruya.getGlobalBounds(), true);
	Collidable mindyCollidable(1, hitboxmindy.getGlobalBounds(), true);
	Collidable bellaCollidable(1, hitboxbella.getGlobalBounds(), true);
	Collidable mantecaCollidable(1, hitboxmanteca.getGlobalBounds(), true);
	Collidable pushiCollidable(1, hitboxpushi.getGlobalBounds(), true);
	Collidable munecaCollidable(1, hitboxmuneca.getGlobalBounds(), true);

	// Check for collisions
	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(playerCollidable.m_bounds)) {

			// Handle collision
			mPlayer.setPosition(previousPlayerPos);
			hitboxplayer.setPosition(previousPlayerPos);
			//cout << "Collision with object!\n";

		}
	}

	// Chiwis Collision
	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(chiwisCollidable.m_bounds)) {
			// Handle collision
			sf::FloatRect intersection;
			if (hitboxchiwis.getGlobalBounds().intersects(collidable.getBounds(), intersection)) {
				// Calculate shortest distance to move hitbox away from intersection
				sf::Vector2f direction = hitboxchiwis.getPosition() - sf::Vector2f(intersection.left + intersection.width / 2, intersection.top + intersection.height / 2);
				float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= distance;
				sf::Vector2f size = hitboxchiwis.getSize();
				float radius = std::sqrt(size.x * size.x + size.y * size.y) / 2.f;

				// Calculate distance to move enemy away from intersection point
				float overlapX = (radius - (intersection.width / 2.f)) * direction.x;
				float overlapY = (radius - (intersection.height / 2.f)) * direction.y;

				// Add randomness to new position calculation
				sf::Vector2f randOffset = sf::Vector2f(((rand() % 51) - 25) * 0.2f, ((rand() % 51) - 25) * 0.2f);
				sf::Vector2f newPosition = hitboxchiwis.getPosition() + sf::Vector2f(overlapX, overlapY) + randOffset;

				// Adjust speed based on distance to collision point
				float speed = ChiwisSpeed * (distance / radius);
				sf::Vector2f velocity = direction * speed;
				hitboxchiwis.move(velocity * deltaTime.asSeconds());
				break;
			}
		}
	}

	// Sheguis Collision
	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(sheguisCollidable.m_bounds)) {

			// Handle collision
			sf::FloatRect intersection;
			if (hitboxsheguis.getGlobalBounds().intersects(collidable.getBounds(), intersection)) {
				// Calculate shortest distance to move hitbox away from intersection
				sf::Vector2f direction = hitboxsheguis.getPosition() - sf::Vector2f(intersection.left + intersection.width / 2, intersection.top + intersection.height / 2);
				float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= distance;
				sf::Vector2f size = hitboxsheguis.getSize();
				float radius = std::sqrt(size.x * size.x + size.y * size.y) / 2.f;

				// Calculate distance to move enemy away from intersection point
				float overlapX = (radius - (intersection.width / 2.f)) * direction.x;
				float overlapY = (radius - (intersection.height / 2.f)) * direction.y;

				// Add randomness to new position calculation
				sf::Vector2f randOffset = sf::Vector2f(((rand() % 51) - 25) * 0.2f, ((rand() % 51) - 25) * 0.2f);
				sf::Vector2f newPosition = hitboxsheguis.getPosition() + sf::Vector2f(overlapX, overlapY) + randOffset;

				// Adjust speed based on distance to collision point
				float speed = SheguisSpeed * (distance / radius);
				sf::Vector2f velocity = direction * speed;
				hitboxsheguis.move(velocity * deltaTime.asSeconds());
			}

		}
	}

	// Soruya Collision
	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(soruyaCollidable.m_bounds)) {

			// Handle collision
			sf::FloatRect intersection;
			if (hitboxsoruya.getGlobalBounds().intersects(collidable.getBounds(), intersection)) {
				// Calculate shortest distance to move hitbox away from intersection
				sf::Vector2f direction = hitboxsoruya.getPosition() - sf::Vector2f(intersection.left + intersection.width / 2, intersection.top + intersection.height / 2);
				float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= distance;
				sf::Vector2f size = hitboxsoruya.getSize();
				float radius = std::sqrt(size.x * size.x + size.y * size.y) / 2.f;

				// Calculate distance to move enemy away from intersection point
				float overlapX = (radius - (intersection.width / 2.f)) * direction.x;
				float overlapY = (radius - (intersection.height / 2.f)) * direction.y;

				// Add randomness to new position calculation
				sf::Vector2f randOffset = sf::Vector2f(((rand() % 51) - 25) * 0.2f, ((rand() % 51) - 25) * 0.2f);
				sf::Vector2f newPosition = hitboxsoruya.getPosition() + sf::Vector2f(overlapX, overlapY) + randOffset;

				// Adjust speed based on distance to collision point
				float speed = SoruyaSpeed * (distance / radius);
				sf::Vector2f velocity = direction * speed;
				hitboxsoruya.move(velocity * deltaTime.asSeconds());
			}

		}
	}

	// Mindy Collision
	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(mindyCollidable.m_bounds)) {
			// Handle collision
			sf::FloatRect intersection;
			if (hitboxmindy.getGlobalBounds().intersects(collidable.getBounds(), intersection)) {
				// Calculate shortest distance to move hitbox away from intersection
				sf::Vector2f direction = hitboxmindy.getPosition() - sf::Vector2f(intersection.left + intersection.width / 2, intersection.top + intersection.height / 2);
				float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= distance;
				sf::Vector2f size = hitboxmindy.getSize();
				float radius = std::sqrt(size.x * size.x + size.y * size.y) / 2.f;

				// Calculate distance to move enemy away from intersection point
				float overlapX = (radius - (intersection.width / 2.f)) * direction.x;
				float overlapY = (radius - (intersection.height / 2.f)) * direction.y;

				// Add randomness to new position calculation
				sf::Vector2f randOffset = sf::Vector2f(((rand() % 51) - 25) * 0.2f, ((rand() % 51) - 25) * 0.2f);
				sf::Vector2f newPosition = hitboxchiwis.getPosition() + sf::Vector2f(overlapX, overlapY) + randOffset;

				// Adjust speed based on distance to collision point
				float speed = MindySpeed * (distance / radius);
				sf::Vector2f velocity = direction * speed;
				hitboxmindy.move(velocity * deltaTime.asSeconds());
				break;
			}

		}
	}

	// Bella Collision
	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(bellaCollidable.m_bounds)) {
			// Handle collision
			sf::FloatRect intersection;
			if (hitboxbella.getGlobalBounds().intersects(collidable.getBounds(), intersection)) {
				// Calculate shortest distance to move hitbox away from intersection
				sf::Vector2f direction = hitboxbella.getPosition() - sf::Vector2f(intersection.left + intersection.width / 2, intersection.top + intersection.height / 2);
				float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= distance;
				sf::Vector2f size = hitboxbella.getSize();
				float radius = std::sqrt(size.x * size.x + size.y * size.y) / 2.f;

				// Calculate distance to move enemy away from intersection point
				float overlapX = (radius - (intersection.width / 2.f)) * direction.x;
				float overlapY = (radius - (intersection.height / 2.f)) * direction.y;

				// Add randomness to new position calculation
				sf::Vector2f randOffset = sf::Vector2f(((rand() % 51) - 25) * 0.2f, ((rand() % 51) - 25) * 0.2f);
				sf::Vector2f newPosition = hitboxbella.getPosition() + sf::Vector2f(overlapX, overlapY) + randOffset;

				// Adjust speed based on distance to collision point
				float speed = BellaSpeed * (distance / radius);
				sf::Vector2f velocity = direction * speed;
				hitboxbella.move(velocity * deltaTime.asSeconds());
				break;
			}

		}
	}

	// Manteca Collision
	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(mantecaCollidable.m_bounds)) {
			// Handle collision
			sf::FloatRect intersection;
			if (hitboxbella.getGlobalBounds().intersects(collidable.getBounds(), intersection)) {
				// Calculate shortest distance to move hitbox away from intersection
				sf::Vector2f direction = hitboxbella.getPosition() - sf::Vector2f(intersection.left + intersection.width / 2, intersection.top + intersection.height / 2);
				float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= distance;
				sf::Vector2f size = hitboxbella.getSize();
				float radius = std::sqrt(size.x * size.x + size.y * size.y) / 2.f;

				// Calculate distance to move enemy away from intersection point
				float overlapX = (radius - (intersection.width / 2.f)) * direction.x;
				float overlapY = (radius - (intersection.height / 2.f)) * direction.y;

				// Add randomness to new position calculation
				sf::Vector2f randOffset = sf::Vector2f(((rand() % 51) - 25) * 0.2f, ((rand() % 51) - 25) * 0.2f);
				sf::Vector2f newPosition = hitboxbella.getPosition() + sf::Vector2f(overlapX, overlapY) + randOffset;

				// Adjust speed based on distance to collision point
				float speed = BellaSpeed * (distance / radius);
				sf::Vector2f velocity = direction * speed;
				hitboxbella.move(velocity * deltaTime.asSeconds());
				break;
			}

		}
	}

	// Pushi Collision
	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(pushiCollidable.m_bounds)) {
			// Handle collision
			sf::FloatRect intersection;
			if (hitboxpushi.getGlobalBounds().intersects(collidable.getBounds(), intersection)) {
				// Calculate shortest distance to move hitbox away from intersection
				sf::Vector2f direction = hitboxpushi.getPosition() - sf::Vector2f(intersection.left + intersection.width / 2, intersection.top + intersection.height / 2);
				float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= distance;
				sf::Vector2f size = hitboxpushi.getSize();
				float radius = std::sqrt(size.x * size.x + size.y * size.y) / 2.f;

				// Calculate distance to move enemy away from intersection point
				float overlapX = (radius - (intersection.width / 2.f)) * direction.x;
				float overlapY = (radius - (intersection.height / 2.f)) * direction.y;

				// Add randomness to new position calculation
				sf::Vector2f randOffset = sf::Vector2f(((rand() % 51) - 25) * 0.2f, ((rand() % 51) - 25) * 0.2f);
				sf::Vector2f newPosition = hitboxpushi.getPosition() + sf::Vector2f(overlapX, overlapY) + randOffset;

				// Adjust speed based on distance to collision point
				float speed = PushiSpeed * (distance / radius);
				sf::Vector2f velocity = direction * speed;
				hitboxpushi.move(velocity * deltaTime.asSeconds());
			}
		}
	}

	// Muneca Collision
	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(munecaCollidable.m_bounds)) {
			// Handle collision
			sf::FloatRect intersection;
			if (hitboxmuneca.getGlobalBounds().intersects(collidable.getBounds(), intersection)) {
				// Calculate shortest distance to move hitbox away from intersection
				sf::Vector2f direction = hitboxmuneca.getPosition() - sf::Vector2f(intersection.left + intersection.width / 2, intersection.top + intersection.height / 2);
				float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= distance;
				sf::Vector2f size = hitboxmuneca.getSize();
				float radius = std::sqrt(size.x * size.x + size.y * size.y) / 2.f;

				// Calculate distance to move enemy away from intersection point
				float overlapX = (radius - (intersection.width / 2.f)) * direction.x;
				float overlapY = (radius - (intersection.height / 2.f)) * direction.y;

				// Add randomness to new position calculation
				sf::Vector2f randOffset = sf::Vector2f(((rand() % 51) - 25) * 0.2f, ((rand() % 51) - 25) * 0.2f);
				sf::Vector2f newPosition = hitboxmuneca.getPosition() + sf::Vector2f(overlapX, overlapY) + randOffset;

				// Adjust speed based on distance to collision point
				float speed = MunecaSpeed * (distance / radius);
				sf::Vector2f velocity = direction * speed;
				hitboxmuneca.move(velocity * deltaTime.asSeconds());
			}

		}
	}

	// Vida Player*************************************************************************************
	
	this->BarraVida(QuitarVida, xPlayer, yPlayer);
	this->BarraVidaAux(xPlayer, yPlayer);

	//*************************************************************************************************

	// Player coordinates
	// cout << mPlayer.getPosition().x << std::endl;
	// cout << mPlayer.getPosition().y;
	// cout << "\n\n";
	
	//*****FLECHA**************************************************************************************
	this->Flecha(xPlayer, yPlayer, mItem.getPosition().x, mItem.getPosition().y);

	float AnguloImp = this->Angulo(xPlayer, yPlayer, hitboxsoruya.getPosition().x, hitboxsoruya.getPosition().y, 3000, 700, SoruyaSpeed);
	cout << AnguloImp << std::endl;
}

/*******************************************************************************************************************************************************************/

void Game::render()
{
	mWindow.clear();
	mWindow.draw(Ocean);
	mWindow.draw(background);
	mWindow.draw(objects);
	mWindow.draw(PizzaLogo);
	mWindow.draw(mItem);
	mWindow.draw(mPlayer);
	mWindow.draw(hitboxplayer);
	mWindow.draw(hitboxchiwis);
	mWindow.draw(hitboxsheguis);
	mWindow.draw(hitboxsoruya);
	mWindow.draw(hitboxmindy);

	if (displayItemPrompt) {
		mWindow.draw(prompt);
	}

	mWindow.draw(hitboxbella);
	mWindow.draw(hitboxmanteca);
	mWindow.draw(hitboxpushi);
	mWindow.draw(hitboxmuneca);
	mWindow.draw(vidaaux);
	mWindow.draw(vida);
	mWindow.draw(Chiwis);
	mWindow.draw(Sheguis);
	mWindow.draw(arrow);
	mWindow.display();

}

//*******************************************************************************************************************************************************************

void Game::Flecha(float xPlayer, float yPlayer, float xItem, float yItem) {

	float dx = xItem - xPlayer;
	float dy = yItem - yPlayer;
	float angle = atan2(dy, dx) * 180 / 3.141592 - 90; // calcular el ángulo en grados
	this->arrow.setRotation(angle); // rotar la flecha
	float arrowOffset = -50.f; // ajusta esto para que la flecha esté en la posición correcta

	// establecer los puntos de la flecha en relación con la posición del jugador
	this->arrow.setPointCount(3);
	this->arrow.setPoint(0, sf::Vector2f(xPlayer, yPlayer));
	this->arrow.setPoint(1, sf::Vector2f(xPlayer - 10.f, yPlayer - 10.f));
	this->arrow.setPoint(2, sf::Vector2f(xPlayer + 10.f, yPlayer - 10.f));
	this->arrow.setFillColor(sf::Color::Yellow);

	// ajustar el origen de la flecha para que esté en la punta superior
	this->arrow.setOrigin(xPlayer, yPlayer - 20.f);

	// ajustar la escala de la flecha
	this->arrow.setScale(1.f,1.f); // ajusta la escala según lo necesites

	// enmarcar el contorno de la flecha de negro
	this->arrow.setOutlineThickness(2.f);
	this->arrow.setOutlineColor(sf::Color::Black);

	// calcular la posición del centro del círculo
	float circleRadius = 80.f; // ajusta el radio del círculo según lo necesites
	sf::Vector2f circleCenter(xPlayer + 15.f, yPlayer + 20.f);

	// calcular la posición de la flecha en el borde del círculo
	float angleRadians = (angle + 90) * 3.141592 / 180; // convertir el ángulo a radianes y ajustar para la orientación de la flecha
	sf::Vector2f arrowPosition(cos(angleRadians) * circleRadius, sin(angleRadians) * circleRadius);

	// ajustar la posición de la flecha en función del centro del círculo
	arrowPosition += circleCenter;

	// establecer la posición de la flecha
	this->arrow.setPosition(arrowPosition.x, arrowPosition.y);
}


//********HITBOXES*****************************************************************
void Game::HitBoxPlayer()
{
	this->hitboxplayer.setPosition(720.f, 725.f);
	this->hitboxplayer.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxplayer.setFillColor(sf::Color::Transparent);
	this->hitboxplayer.setOutlineColor(sf::Color::Transparent);
	this->hitboxplayer.setOutlineThickness(4.f);

}

void Game::HitBoxChiwis()
{
	this->hitboxchiwis.setPosition(3000.f, 700.f);
	this->hitboxchiwis.setSize(sf::Vector2f(ChiwisWidth, ChiwisHeight));
	this->hitboxchiwis.setFillColor(sf::Color::Transparent);
	this->hitboxchiwis.setOutlineColor(sf::Color::Cyan);
	this->hitboxchiwis.setOutlineThickness(6.f);
}

void Game::HitBoxSheguis()
{
	this->hitboxsheguis.setPosition(2000.f, 2100.f);
	this->hitboxsheguis.setSize(sf::Vector2f(SheguisWidth, SheguisHeight));
	this->hitboxsheguis.setFillColor(sf::Color::Transparent);
	this->hitboxsheguis.setOutlineColor(sf::Color::Red);
	this->hitboxsheguis.setOutlineThickness(6.f);
}

void Game::HitBoxSoruya()
{
	this->hitboxsoruya.setPosition(3000.f, 700.f);
	this->hitboxsoruya.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxsoruya.setFillColor(sf::Color::Transparent);
	this->hitboxsoruya.setOutlineColor(sf::Color::Black);
	this->hitboxsoruya.setOutlineThickness(6.f);
}

void Game::HitBoxMindy()
{
	this->hitboxmindy.setPosition(1816.f, 1466.f);
	this->hitboxmindy.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxmindy.setFillColor(sf::Color::Transparent);
	this->hitboxmindy.setOutlineColor(sf::Color::Black);
	this->hitboxmindy.setOutlineThickness(6.f);
}


void Game::HitBoxBella()
{
	this->hitboxbella.setPosition(85.f, 790.f);
	this->hitboxbella.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxbella.setFillColor(sf::Color::Transparent);
	this->hitboxbella.setOutlineColor(sf::Color::Black);
	this->hitboxbella.setOutlineThickness(6.f);
}

void Game::HitBoxManteca()
{
	this->hitboxmanteca.setPosition(2366.f, 2800.f);
	this->hitboxmanteca.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxmanteca.setFillColor(sf::Color::Transparent);
	this->hitboxmanteca.setOutlineColor(sf::Color::Black);
	this->hitboxmanteca.setOutlineThickness(6.f);
}

void Game::HitBoxPushi()
{
	this->hitboxpushi.setPosition(85.f, 1950.f);
	this->hitboxpushi.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxpushi.setFillColor(sf::Color::Transparent);
	this->hitboxpushi.setOutlineColor(sf::Color::Black);
	this->hitboxpushi.setOutlineThickness(6.f);
}

void Game::HitBoxMuneca()
{
	this->hitboxmuneca.setPosition(1500.f, 2415.f);
	this->hitboxmuneca.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxmuneca.setFillColor(sf::Color::Transparent);
	this->hitboxmuneca.setOutlineColor(sf::Color::Black);
	this->hitboxmuneca.setOutlineThickness(6.f);
}


void Game::BarraVida(float QuitarVida, float xPlayer, float yPlayer) {

		this->vida.setPosition(xPlayer - 2.f, yPlayer - 20.f);
		this->vida.setSize(sf::Vector2f(CantVida - QuitarVida, 10.f));

		if (QuitarVida >= CantVida - 1.f) {
			this->vida.setFillColor(sf::Color::Red);
		}
		else {
			this->vida.setFillColor(sf::Color::Green);
		}
		this->vida.setOutlineColor(sf::Color::Transparent);
		this->vida.setOutlineThickness(3.f);
	

}

void Game::BarraVidaAux(float xPlayer, float yPlayer) {

	this->vidaaux.setPosition(xPlayer - 2.f, yPlayer - 20.f);
	this->vidaaux.setSize(sf::Vector2f(CantVida, 10.f));
	this->vidaaux.setFillColor(sf::Color::Red);
	this->vidaaux.setOutlineColor(sf::Color::Black);
	this->vidaaux.setOutlineThickness(3.f);
}


/*******************************************************************************************************************************************************************/

void Game::Seguir(float xPlayer, float yPlayer, float xMascota, float yMascota, float Pox, float Poy, float Speed, sf::RectangleShape& hitboxmascota, sf::Time deltaTime) {
	float dx = xPlayer - xMascota;
	float dy = yPlayer - yMascota;
	float distance = sqrt(pow(dx, 2.f) + pow(dy, 2.f));

	float dxaux = Pox - xMascota;
	float dyaux = Poy - yMascota;
	float distanceaux = sqrt(pow(dxaux, 2.f) + pow(dyaux, 2.f));

	sf::Vector2f unitVector(dx / distance, dy / distance);
	sf::Vector2f unitVectoraux(dxaux / (distanceaux + 0.1), dyaux / (distanceaux + 0.1));

	sf::Vector2f velocity = unitVector * (Speed);
	sf::Vector2f velocityaux = unitVectoraux * (Speed);

	if (distance <= RadioDetected && distanceaux <= RadioDetected) {
		hitboxmascota.move(velocity * deltaTime.asSeconds());
	}
	else {
		hitboxmascota.move(velocityaux * deltaTime.asSeconds());
	}
}

float Game::Angulo(float xPlayer, float yPlayer, float xMascota, float yMascota, float Pox, float Poy, const float Speed) {
	float dx = xPlayer - xMascota;
	float dy = yPlayer - yMascota;
	float distance = sqrt(pow(dx, 2.f) + pow(dy, 2.f));

	float dxaux = Pox - xMascota;
	float dyaux = Poy - yMascota;
	float distanceaux = sqrt(pow(dxaux, 2.f) + pow(dyaux, 2.f));

	sf::Vector2f unitVector(dx / distance, dy / distance);
	sf::Vector2f unitVectoraux(dxaux / (distanceaux + 0.1), dyaux / (distanceaux + 0.1));

	sf::Vector2f velocity = unitVector * (Speed);
	sf::Vector2f velocityaux = unitVectoraux * (Speed);

	if (distance <= RadioDetected && distanceaux <= RadioDetected) {
		float angle = atan2(velocity.y, velocity.x) * 180 / 3.141592 + 180.f;
		return angle ;
	}
	else {
		float angle = atan2(velocityaux.y, velocityaux.x) * 180/3.141592 + 180.f;
		return angle;
	}
}


//NOOOO BORRRARRR ES POR SI UNA EMERGENCIA
/*
	float dxmanteca = mPlayer.getPosition().x - hitboxmanteca.getPosition().x;
	float dymanteca = mPlayer.getPosition().y - hitboxmanteca.getPosition().y;
	float distancemanteca = sqrt(pow(dxmanteca, 2.f) + pow(dymanteca, 2.f));

	float dxmantecaaux = 2366.f - hitboxmanteca.getPosition().x;
	float dymantecaaux = 2800.f - hitboxmanteca.getPosition().y;
	float distancemantecaaux = sqrt(pow(dxmantecaaux, 2.f) + pow(dymantecaaux, 2.f));

	sf::Vector2f unitVectormanteca(dxmanteca / distancemanteca, dymanteca / distancemanteca);
	sf::Vector2f unitVectormantecaaux(dxmantecaaux / (distancemantecaaux + 0.001), dymantecaaux / (distancemantecaaux + 0.001));

	sf::Vector2f velocitymanteca = unitVectormanteca * (MantecaSpeed);
	sf::Vector2f velocitymantecaaux = unitVectormantecaaux * (MantecaSpeed);

	if (distancemanteca <= RadioDetected && distancemantecaaux <= RadioDetected) {
		hitboxmanteca.move(velocitymanteca * deltaTime.asSeconds());
	}
	else {
		hitboxmanteca.move(velocitymantecaaux * deltaTime.asSeconds());
	}
	*/