// basado en el libro SFML Game Development :)

#include "Game.h"
#include <cmath>


Game::Game()
	: mWindow(sf::VideoMode(800, 600), "Pizza Panic")
	, mTexture()
	, mPlayer()
	, pView(sf::FloatRect(0.f, 0.f, mWindow.getSize().x, mWindow.getSize().y))
	, mainMenu(m_font, m_menuBackground)
{
	// Initialize MainMenu
	if (!m_font.loadFromFile("Fonts/ka1.ttf"))
	{
		// Handle loading error
		cout << ("Error al cargar el font.");
	}
    if (!m_font2.loadFromFile("Fonts/font2.ttf"))
    {
        // Handle loading error
        cout << ("Error al cargar el font del item.");
    }
	if (!m_menuBackground.loadFromFile("Images/FondoMenu.png"))
	{
		// Handle loading error
		cout << ("Error al cargar el fondo del menu.");
	}
	MainMenu mainMenu(m_font, m_menuBackground);

	// Player
	if (!mTexture.loadFromFile("Images/robot-idle.gif"))
	{
		// Handle loading error
		cout << ("Error al cargar el archivo.");
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(2500.f, 2500.f);
	mPlayer.setScale(0.18f, 0.18f);

    // Textura del Item
    if (!mItemTexture.loadFromFile("Images/Eagle.png"))
    {
        // Handle loading error
        cout << ("Error al cargar el archivo del Item.");
    }
    mItem.setTexture(mItemTexture);
    mItem.setPosition(3070.f, 2760.f);
    mItem.setScale(1.f,1.f);

    // Texto del item
    prompt.setFont(m_font2);
    prompt.setString("Presiona espacio para recoger el item!");
    prompt.setPosition(mItem.getPosition().x - 300,mItem.getPosition().y + 100);

	// Hitboxes
	this->HitBoxPlayer();
	this->HitBoxChiwis();
	this->HitBoxSheguis();
	this->HitBoxSoruya();
	this->HitBoxMindy();
	this->HitBoxBella();
	this->HitBoxManteca();
	this->HitBoxPushi();
	this->HitBoxMuneca();

	// Tilemap
	if (!background.load("Images/Tileset.png", sf::Vector2u(48, 48)))
	{
		// Handle loading error
		cout << ("Error al cargar el mapa.");
	}

	// Collision objects
	if (!objects.load("Images/Tileset.png", sf::Vector2u(48, 48)))
	{
		// Handle loading error
		cout << ("Error al cargar los objetos del mapa.");
	}

	// Music
	if (!music.openFromFile("Audios/CreepyForest.wav")) // canci�n de prueba nom�s
	{
		// Handle loading error
		cout << ("Error al cargar el audio.");
	}
	//music.play();
	music.setVolume(20.f);

}

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

void Game::run()
{
	showMainMenu();

	// If Play button is clicked, start the game
	if (mainMenu.getSelectedOption() == MainMenu::Option::Jugar) {

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
		}
	}

}

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

	// Camera follows player
	pView.setCenter(mPlayer.getPosition());
	pView.setSize(1000.f, 1000.f);
	mWindow.setView(pView);

    // Update Item and Player collision boundaries
    mItemCollider = mItem.getGlobalBounds();
    mPlayerCollider = mPlayer.getGlobalBounds();

    // Check item collision
    displayItemPrompt = false;
    if(mPlayerCollider.intersects(mItemCollider)){

        displayItemPrompt = true;

        if(sf::Keyboard::isKeyPressed(teclaItem)) {
            // Perform item pickup logic here
            cout << "Item picked up!" << std::endl;
            mItem.setPosition(-1000.f,-1000.f);
        }
    }

	

	//**************SHEGUIS**************************************************
	
	float dxsheguis = mPlayer.getPosition().x - hitboxsheguis.getPosition().x;
	float dysheguis = mPlayer.getPosition().y - hitboxsheguis.getPosition().y;
	float distancesheguis = sqrt(pow(dxsheguis, 2.f) + pow(dysheguis, 2.f));

	float dxsheguisaux = 2000.f - hitboxsheguis.getPosition().x;
	float dysheguisaux = 2100.f - hitboxsheguis.getPosition().y;
	float distancesheguisaux = sqrt(pow(dxsheguisaux, 2.f) + pow(dysheguisaux, 2.f));

	sf::Vector2f unitVectorsheguis(dxsheguis / distancesheguis, dysheguis / distancesheguis);
	sf::Vector2f unitVectorsheguisaux(dxsheguisaux / (distancesheguisaux + 0.001), dysheguisaux / (distancesheguisaux + 0.001));

	sf::Vector2f velocitysheguis = unitVectorsheguis * (SheguisSpeed);
	sf::Vector2f velocitysheguisaux = unitVectorsheguisaux * (SheguisSpeed);

	if (distancesheguis <= RadioDetected && distancesheguisaux <= RadioDetected) {
		hitboxsheguis.move(velocitysheguis * deltaTime.asSeconds());
	}
	else {
		hitboxsheguis.move(velocitysheguisaux * deltaTime.asSeconds());
	}
	//************************************************************************


	//**************SORUYA****************************************************
	
	float dxsoruya = mPlayer.getPosition().x - hitboxsoruya.getPosition().x;
	float dysoruya = mPlayer.getPosition().y - hitboxsoruya.getPosition().y;
	float distancesoruya = sqrt(pow(dxsoruya, 2.f) + pow(dysoruya, 2.f));

	float dxsoruyaaux = 3000.f - hitboxsoruya.getPosition().x;
	float dysoruyaaux = 700.f - hitboxsoruya.getPosition().y;
	float distancesoruyaaux = sqrt(pow(dxsoruyaaux, 2.f) + pow(dysoruyaaux, 2.f));

	sf::Vector2f unitVectorsoruya(dxsoruya / distancesoruya, dysoruya / distancesoruya);
	sf::Vector2f unitVectorsoruyaaux(dxsoruyaaux / (distancesoruyaaux + 0.001), dysoruyaaux / (distancesoruyaaux + 0.001));

	sf::Vector2f velocitysoruya = unitVectorsoruya * (SoruyaSpeed);
	sf::Vector2f velocitysoruyaaux = unitVectorsoruyaaux * (SoruyaSpeed);

	if (distancesoruya <= RadioDetected && distancesoruyaaux <= RadioDetected) {
		hitboxsoruya.move(velocitysoruya * deltaTime.asSeconds());
	}
	else {
		hitboxsoruya.move(velocitysoruyaaux * deltaTime.asSeconds());
	}
	//**************************************************************************


	//**************MINDY****************************************************

	float dxmindy = mPlayer.getPosition().x - hitboxmindy.getPosition().x;
	float dymindy = mPlayer.getPosition().y - hitboxmindy.getPosition().y;
	float distancemindy = sqrt(pow(dxmindy, 2.f) + pow(dymindy, 2.f));

	float dxmindyaux = 1816.f - hitboxmindy.getPosition().x;
	float dymindyaux = 1416.f - hitboxmindy.getPosition().y;
	float distancemindyaux = sqrt(pow(dxmindyaux, 2.f) + pow(dymindyaux, 2.f));

	sf::Vector2f unitVectormindy(dxmindy / distancemindy, dymindy / distancemindy);
	sf::Vector2f unitVectormindyaux(dxmindyaux / (distancemindyaux + 0.001), dymindyaux / (distancemindyaux + 0.001));

	sf::Vector2f velocitymindy = unitVectormindy * (MindySpeed);
	sf::Vector2f velocitymindyaux = unitVectormindyaux * (MindySpeed);

	if (distancemindy <= RadioDetected && distancemindyaux <= RadioDetected) {
		hitboxmindy.move(velocitymindy * deltaTime.asSeconds());
	}
	else {
		hitboxmindy.move(velocitymindyaux * deltaTime.asSeconds());
	}
	//**************************************************************************


	//**************BELLA****************************************************

	float dxbella = mPlayer.getPosition().x - hitboxbella.getPosition().x;
	float dybella = mPlayer.getPosition().y - hitboxbella.getPosition().y;
	float distancebella = sqrt(pow(dxbella, 2.f) + pow(dybella, 2.f));

	float dxbellaaux = 85.f - hitboxbella.getPosition().x;
	float dybellaaux = 790.f - hitboxbella.getPosition().y;
	float distancebellaaux = sqrt(pow(dxbellaaux, 2.f) + pow(dybellaaux, 2.f));

	sf::Vector2f unitVectorbella(dxbella / distancebella, dybella / distancebella);
	sf::Vector2f unitVectorbellaaux(dxbellaaux / (distancebellaaux + 0.001), dybellaaux / (distancebellaaux + 0.001));

	sf::Vector2f velocitybella = unitVectorbella * (BellaSpeed);
	sf::Vector2f velocitybellaaux = unitVectorbellaaux * (BellaSpeed);

	if (distancebella <= RadioDetected && distancebellaaux <= RadioDetected) {
		hitboxbella.move(velocitybella * deltaTime.asSeconds());
	}
	else {
		hitboxbella.move(velocitybellaaux * deltaTime.asSeconds());
	}
	//**************************************************************************


	//**************MANTECA****************************************************

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
	
	//**************************************************************************

	//**************PUSHI****************************************************

	float dxpushi = mPlayer.getPosition().x - hitboxpushi.getPosition().x;
	float dypushi = mPlayer.getPosition().y - hitboxpushi.getPosition().y;
	float distancepushi = sqrt(pow(dxpushi, 2.f) + pow(dypushi, 2.f));

	float dxpushiaux = 85.f - hitboxpushi.getPosition().x;
	float dypushiaux = 1950.f - hitboxpushi.getPosition().y;
	float distancepushiaux = sqrt(pow(dxpushiaux, 2.f) + pow(dypushiaux, 2.f));

	sf::Vector2f unitVectorpushi(dxpushi / distancepushi, dypushi / distancepushi);
	sf::Vector2f unitVectorpushiaux(dxpushiaux / (distancepushiaux + 0.001), dypushiaux / (distancepushiaux + 0.001));

	sf::Vector2f velocitypushi = unitVectorpushi * (PushiSpeed);
	sf::Vector2f velocitypushiaux = unitVectorpushiaux * (PushiSpeed);

	if (distancepushi <= RadioDetected && distancepushiaux <= RadioDetected) {
		hitboxpushi.move(velocitypushi * deltaTime.asSeconds());
	}
	else {
		hitboxpushi.move(velocitypushiaux * deltaTime.asSeconds());
	}

	//**************************************************************************

	//**************MUNECA****************************************************

	float dxmuneca = mPlayer.getPosition().x - hitboxmuneca.getPosition().x;
	float dymuneca = mPlayer.getPosition().y - hitboxmuneca.getPosition().y;
	float distancemuneca = sqrt(pow(dxmuneca, 2.f) + pow(dymuneca, 2.f));

	float dxmunecaaux = 1500.f - hitboxmuneca.getPosition().x;
	float dymunecaaux = 2415.f - hitboxmuneca.getPosition().y;
	float distancemunecaaux = sqrt(pow(dxmunecaaux, 2.f) + pow(dymunecaaux, 2.f));

	sf::Vector2f unitVectormuneca(dxmuneca / distancemuneca, dymuneca / distancemuneca);
	sf::Vector2f unitVectormunecaaux(dxmunecaaux / (distancemunecaaux + 0.001), dymunecaaux / (distancemunecaaux + 0.001));

	sf::Vector2f velocitymuneca = unitVectormuneca * (MunecaSpeed);
	sf::Vector2f velocitymunecaaux = unitVectormunecaaux * (MunecaSpeed);

	if (distancemuneca <= RadioDetected && distancemunecaaux <= RadioDetected) {
		hitboxmuneca.move(velocitymuneca * deltaTime.asSeconds());
	}
	else {
		hitboxmuneca.move(velocitymunecaaux * deltaTime.asSeconds());
	}
	//**************************************************************************


	//*************CHIWIS*******************************************************
	float dxchiwis = mPlayer.getPosition().x - hitboxchiwis.getPosition().x;
	float dychiwis = mPlayer.getPosition().y - hitboxchiwis.getPosition().y;
	float distancechiwis = sqrt(pow(dxchiwis, 2.f) + pow(dychiwis, 2.f));
	sf::Vector2f unitVectorchiwis(dxchiwis / distancechiwis, dychiwis / distancechiwis);
	sf::Vector2f velocitychiwis = unitVectorchiwis * (ChiwisSpeed);
	hitboxchiwis.move(velocitychiwis * deltaTime.asSeconds());
	//**************************************************************************
	


	// Keep track of the player's previous position
	sf::Vector2f previousPlayerPos = mPlayer.getPosition();
	mPlayer.move(movement * deltaTime.asSeconds());
	hitboxplayer.move(movement * deltaTime.asSeconds());
	
	
	// Create Collidable object for the player
	Collidable playerCollidable(1, mPlayer.getGlobalBounds(), true);


	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(playerCollidable.m_bounds)) {

			// Handle collision
			mPlayer.setPosition(previousPlayerPos);
			hitboxplayer.setPosition(previousPlayerPos);
			//cout << "Collision with object!\n";

		}
	}


<<<<<<< HEAD
//	cout << hitboxsoruya.getPosition().x << std::endl;
//	cout << hitboxsoruya.getPosition().y;
//	cout << "\n\n";
=======
	cout << mPlayer.getPosition().x << std::endl;
	cout << mPlayer.getPosition().y;
	cout << "\n\n";
>>>>>>> 9080f614ab62beaeb6abc3d356a0a2add9ef35c2
}



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
	this->hitboxchiwis.setPosition(3250.f, 1215.f);
	this->hitboxchiwis.setSize(sf::Vector2f(40.f, 40.f));
	this->hitboxchiwis.setFillColor(sf::Color::Transparent);
	this->hitboxchiwis.setOutlineColor(sf::Color::Cyan);
	this->hitboxchiwis.setOutlineThickness(6.f);
}

void Game::HitBoxSheguis()
{
	this->hitboxsheguis.setPosition(2000.f, 2100.f);
	this->hitboxsheguis.setSize(sf::Vector2f(40.f, 40.f));
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


void Game::render()
{
	mWindow.clear();
	mWindow.draw(background);
	mWindow.draw(objects);
	mWindow.draw(mPlayer);
    mWindow.draw(mItem);
    mWindow.draw(hitboxplayer);
	mWindow.draw(hitboxchiwis);
	mWindow.draw(hitboxsheguis);
	mWindow.draw(hitboxsoruya);
	mWindow.draw(hitboxmindy);
<<<<<<< HEAD
    if (displayItemPrompt){
        mWindow.draw(prompt);
    }
=======
	mWindow.draw(hitboxbella);
	mWindow.draw(hitboxmanteca);
	mWindow.draw(hitboxpushi);
	mWindow.draw(hitboxmuneca);
>>>>>>> 9080f614ab62beaeb6abc3d356a0a2add9ef35c2
	mWindow.display();

}

/* void Game::Seguir(float xP, float yP, float xM, float yM, float Pox, float Poy, float Speed, sf::RectangleShape hitboxmascota, sf::Time deltaTime) {
	float dx = xP - xM;
	float dy = yP - yM;
	float distance = sqrt(pow(dx, 2.f) + pow(dy, 2.f));

	float dxaux = Pox - xM;
	float dyaux = Poy - yM;
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
*/
