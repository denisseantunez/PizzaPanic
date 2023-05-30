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

void Game::run()
{
	do {
		// Initialize variables
		mainMenu.resetSelectedOption();
		processEvents();
		mordidas = 0.f;
		quitarVida = 0.f;
		mItem.setTexture(mItemTexture);
		mItem.setPosition(3070.f, 2760.f);
		mPlayer.setPosition(2500.f, 2500.f);
		mItem.setScale(1.7f, 1.7f);
		chiwis.hitbox.setPosition(3000.f, 700.f);
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
			while (mWindow.isOpen()){
				processEvents();
				timeSinceLastUpdate += clock.restart();
				while (timeSinceLastUpdate > TimePerFrame){
					timeSinceLastUpdate -= TimePerFrame;
					processEvents();
					update(TimePerFrame);
				}
				render();
				// If player dies
				if (mordidas == 120) {
					PizzasEntregadas = 0;
					mItem.setPosition(3070.f, 2760.f);
					cargandoItem = false;
					music.stop();
					deathSound.play();
					deathSound.setLoop(true);
			
					GameOver.setPosition(mPlayer.getPosition().x - 460.f, mPlayer.getPosition().y - 500.f);
					mWindow.clear();
					mWindow.draw(GameOver);
					mWindow.display();
                    std::this_thread::sleep_for(std::chrono::seconds(2));
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

	// Sprite Animations ***************************
	if (clock.getElapsedTime().asSeconds() > 0.1f) {
		// Player Animations
		if (m_playerRect.left == 1920)
			m_playerRect.left = 0;
		else { m_playerRect.left += 320; }

		// Chiwis Animations
		float AnguloChiwis = this->AnguloChiwis(xPlayer, yPlayer, chiwis.hitbox.getPosition().x, chiwis.hitbox.getPosition().y, ChiwisSpeed);

		if ((AnguloChiwis >= 70 && AnguloChiwis <= 110) || (AnguloChiwis >= -290 && AnguloChiwis <= -250)) { // ARRIBA
			chiwis.texRect.top = 498;
			if (chiwis.texRect.left == 104)
				chiwis.texRect.left = 0;
			else
				chiwis.texRect.left += 52;
		}
		else if (AnguloChiwis > 110 && AnguloChiwis < 250) { // DERECHA
			chiwis.texRect.top = 429;
			if (chiwis.texRect.left == 104)
				chiwis.texRect.left = 0;
			else
				chiwis.texRect.left += 52;
		}
		else if ((AnguloChiwis >= 250 && AnguloChiwis <= 290) || (AnguloChiwis >= -110 && AnguloChiwis <= -70)) { // ABAJO
			chiwis.texRect.top = 287;
			if (chiwis.texRect.left == 104)
				chiwis.texRect.left = 0;
			else
				chiwis.texRect.left += 52;
		}
		else {
			if (AnguloChiwis > 0 || (AnguloChiwis > -250 && AnguloChiwis < -110)) { // IZQUIERDA
				chiwis.texRect.top = 358; // IZQUIERDA
				if (chiwis.texRect.left == 104)
					chiwis.texRect.left = 0;
				else
					chiwis.texRect.left += 52;
			}
			else {
				chiwis.texRect.top = 429; // DERECHA
				if (chiwis.texRect.left == 104)
					chiwis.texRect.left = 0;
				else
					chiwis.texRect.left += 52;
			}
		}

		sheguis.animate(xPlayer, yPlayer, 2000.f, 2100.f);
		soruya.animate(xPlayer, yPlayer, 3000.f, 700.f);
		mindy.animate(xPlayer, yPlayer, 1816.f, 1466.f);
		bella.animate(xPlayer, yPlayer, 85.f, 790.f);
		manteca.animate(xPlayer, yPlayer, 2366, 2800);
		pushi.animate(yPlayer, yPlayer, 85.f, 1950.f);
		muneca.animate(xPlayer, yPlayer, 1500.f, 2415.f);

		// Mindy Animations
		//float AnguloMindy = this->Angulo(xPlayer, yPlayer, hitboxmindy.getPosition().x, hitboxmindy.getPosition().y, 1816, 1466, MindySpeed);

		//if ((AnguloMindy >= 70 && AnguloMindy <= 110) || (AnguloMindy >= -290 && AnguloMindy <= -250)) { // ARRIBA
		//	mindyTexRect.top = 498;
		//	if (mindyTexRect.left == 260)
		//		mindyTexRect.left = 156;
		//	else
		//		mindyTexRect.left += 52;
		//}
		//else if (AnguloMindy > 110 && AnguloMindy < 250) { // DERECHA
		//	mindyTexRect.top = 429;
		//	if (mindyTexRect.left == 260)
		//		mindyTexRect.left = 156;
		//	else
		//		mindyTexRect.left += 52;
		//}
		//else if ((AnguloMindy >= 250 && AnguloMindy <= 290) || (AnguloMindy >= -110 && AnguloMindy <= -70)) { // ABAJO
		//	mindyTexRect.top = 287;
		//	if (mindyTexRect.left == 260)
		//		mindyTexRect.left = 156;
		//	else
		//		mindyTexRect.left += 52;
		//}
		//else {
		//	if (AnguloMindy > 0 || (AnguloMindy > -250 && AnguloMindy < -110)) { // IZQUIERDA
		//		mindyTexRect.top = 358; // IZQUIERDA
		//		if (mindyTexRect.left == 260)
		//			mindyTexRect.left = 156;
		//		else
		//			mindyTexRect.left += 52;
		//	}
		//	else {
		//		mindyTexRect.top = 429; // DERECHA
		//		if (mindyTexRect.left == 260)
		//			mindyTexRect.left = 156;
		//		else
		//			mindyTexRect.left += 52;
		//	}
		//}

		// Bella Animations
		//float AnguloBella = this->Angulo(xPlayer, yPlayer, hitboxbella.getPosition().x, hitboxbella.getPosition().y, 85, 790, BellaSpeed);

		//if ((AnguloBella >= 70 && AnguloBella <= 110) || (AnguloBella >= -290 && AnguloBella <= -250)) { // ARRIBA
		//	bellaTexRect.top = 498;
		//	if (bellaTexRect.left == 572)
		//		bellaTexRect.left = 468;
		//	else
		//		bellaTexRect.left += 52;
		//}
		//else if (AnguloBella > 110 && AnguloBella < 250) { // DERECHA
		//	bellaTexRect.top = 429;
		//	if (bellaTexRect.left == 572)
		//		bellaTexRect.left = 468;
		//	else
		//		bellaTexRect.left += 52;
		//}
		//else if ((AnguloBella >= 250 && AnguloBella <= 290) || (AnguloBella >= -110 && AnguloBella <= -70)) { // ABAJO
		//	bellaTexRect.top = 287;
		//	if (bellaTexRect.left == 572)
		//		bellaTexRect.left = 468;
		//	else
		//		bellaTexRect.left += 52;
		//}
		//else {
		//	if (AnguloBella > 0 || (AnguloBella > -250 && AnguloBella < -110)) { // IZQUIERDA
		//		bellaTexRect.top = 358; // IZQUIERDA
		//		if (bellaTexRect.left == 572)
		//			bellaTexRect.left = 468;
		//		else
		//			bellaTexRect.left += 52;
		//	}
		//	else {
		//		bellaTexRect.top = 429; // DERECHA
		//		if (bellaTexRect.left == 572)
		//			bellaTexRect.left = 468;
		//		else
		//			bellaTexRect.left += 52;
		//	}
		//}

		// Manteca Animations
		//float AnguloManteca = this->Angulo(xPlayer, yPlayer, hitboxmanteca.getPosition().x, hitboxmanteca.getPosition().y, 2366, 2800, MantecaSpeed);

		//if ((AnguloManteca >= 70 && AnguloManteca <= 110) || (AnguloManteca >= -290 && AnguloManteca <= -250)) { // ARRIBA
		//	mantecaTexRect.top = 498;
		//	if (mantecaTexRect.left == 416)
		//		mantecaTexRect.left = 312;
		//	else
		//		mantecaTexRect.left += 52;
		//}
		//else if (AnguloManteca > 110 && AnguloManteca < 250) { // DERECHA
		//	mantecaTexRect.top = 429;
		//	if (mantecaTexRect.left == 416)
		//		mantecaTexRect.left = 312;
		//	else
		//		mantecaTexRect.left += 52;
		//}
		//else if ((AnguloManteca >= 250 && AnguloManteca <= 290) || (AnguloManteca >= -110 && AnguloManteca <= -70)) { // ABAJO
		//	mantecaTexRect.top = 287;
		//	if (mantecaTexRect.left == 416)
		//		mantecaTexRect.left = 312;
		//	else
		//		mantecaTexRect.left += 52;
		//}
		//else {
		//	if (AnguloManteca > 0 || (AnguloManteca > -250 && AnguloManteca < -110)) { // IZQUIERDA
		//		mantecaTexRect.top = 358; // IZQUIERDA
		//		if (mantecaTexRect.left == 416)
		//			mantecaTexRect.left = 312;
		//		else
		//			mantecaTexRect.left += 52;
		//	}
		//	else {
		//		mantecaTexRect.top = 429; // DERECHA
		//		if (mantecaTexRect.left == 416)
		//			mantecaTexRect.left = 312;
		//		else
		//			mantecaTexRect.left += 52;
		//	}
		//}

		// Pushi Animations
		//float AnguloPushi = this->Angulo(xPlayer, yPlayer, hitboxpushi.getPosition().x, hitboxpushi.getPosition().y, 85, 1950, PushiSpeed);

		//if ((AnguloPushi >= 70 && AnguloPushi <= 110) || (AnguloPushi >= -290 && AnguloPushi <= -250)) { // ARRIBA
		//	pushiTexRect.top = 213;
		//	if (pushiTexRect.left == 416)
		//		pushiTexRect.left = 312;
		//	else
		//		pushiTexRect.left += 52;
		//}
		//else if (AnguloPushi > 110 && AnguloPushi < 250) { // DERECHA
		//	pushiTexRect.top = 142;
		//	if (pushiTexRect.left == 416)
		//		pushiTexRect.left = 312;
		//	else
		//		pushiTexRect.left += 52;
		//}
		//else if ((AnguloPushi >= 250 && AnguloPushi <= 290) || (AnguloPushi >= -110 && AnguloPushi <= -70)) { // ABAJO
		//	pushiTexRect.top = 0;
		//	if (pushiTexRect.left == 416)
		//		pushiTexRect.left = 312;
		//	else
		//		pushiTexRect.left += 52;
		//}
		//else {
		//	if (AnguloPushi > 0 || (AnguloPushi > -250 && AnguloPushi < -110)) { // IZQUIERDA
		//		pushiTexRect.top = 71; // IZQUIERDA
		//		if (pushiTexRect.left == 416)
		//			pushiTexRect.left = 312;
		//		else
		//			pushiTexRect.left += 52;
		//	}
		//	else {
		//		pushiTexRect.top = 142; // DERECHA
		//		if (pushiTexRect.left == 416)
		//			pushiTexRect.left = 312;
		//		else
		//			pushiTexRect.left += 52;
		//	}
		//}

		// Muneca Animations
		//float AnguloMuneca = this->Angulo(xPlayer, yPlayer, hitboxmuneca.getPosition().x, hitboxmuneca.getPosition().y, 1500, 2415, MunecaSpeed);

		//if ((AnguloMuneca >= 70 && AnguloMuneca <= 110) || (AnguloMuneca >= -290 && AnguloMuneca <= -250)) { // ARRIBA
		//	munecaTexRect.top = 213;
		//	if (munecaTexRect.left == 572)
		//		munecaTexRect.left = 468;
		//	else
		//		munecaTexRect.left += 52;
		//}
		//else if (AnguloMuneca > 110 && AnguloMuneca < 250) { // DERECHA
		//	munecaTexRect.top = 142;
		//	if (munecaTexRect.left == 572)
		//		munecaTexRect.left = 468;
		//	else
		//		munecaTexRect.left += 52;
		//}
		//else if ((AnguloMuneca >= 250 && AnguloMuneca <= 290) || (AnguloMuneca >= -110 && AnguloMuneca <= -70)) { // ABAJO
		//	munecaTexRect.top = 0;
		//	if (munecaTexRect.left == 572)
		//		munecaTexRect.left = 468;
		//	else
		//		munecaTexRect.left += 52;
		//}
		//else {
		//	if (AnguloMuneca > 0 || (AnguloMuneca > -250 && AnguloMuneca < -110)) { // IZQUIERDA
		//		munecaTexRect.top = 71; // IZQUIERDA
		//		if (munecaTexRect.left == 572)
		//			munecaTexRect.left = 468;
		//		else
		//			munecaTexRect.left += 52;
		//	}
		//	else {
		//		munecaTexRect.top = 142; // DERECHA
		//		if (munecaTexRect.left == 572)
		//			munecaTexRect.left = 468;
		//		else
		//			munecaTexRect.left += 52;
		//	}
		//	
		//}

		// Set Sprite Textures Rectangles
		mPlayer.setTextureRect(m_playerRect);
		chiwis.sprite.setTextureRect(chiwis.texRect);
		//sheguis.sprite.setTextureRect(sheguis.texRect);
		//soruya.sprite.setTextureRect(soruya.texRect);
		//mindy.sprite.setTextureRect(mindy.texRect);
		//bella.sprite.setTextureRect(bella.texRect);
		//manteca.sprite.setTextureRect(manteca.texRect);
		//pushi.sprite.setTextureRect(pushi.texRect);
		//muneca.sprite.setTextureRect(muneca.texRect);
		clock.restart();
	}

	// Camera follows player ************************************************************************
	pView.setCenter(mPlayer.getPosition());
	pView.setSize(1000.f, 1000.f);
	mWindow.setView(pView);

	// Update item and player collision boundaries *****************
	mItemCollider = mItem.getGlobalBounds();
	mItemArrowCollider = mItemArrow.getGlobalBounds();
	mPlayerCollider = mPlayer.getGlobalBounds();
	/*ChiwisCollider = hitboxchiwis.getGlobalBounds();
	SheguisCollider = hitboxsheguis.getGlobalBounds();
	SoruyaCollider = hitboxsoruya.getGlobalBounds();
	MindyCollider = hitboxmindy.getGlobalBounds();
	MantecaCollider = hitboxmanteca.getGlobalBounds();
	MunecaCollider = hitboxmuneca.getGlobalBounds();
	PushiCollider = hitboxpushi.getGlobalBounds();
	BellaCollider = hitboxbella.getGlobalBounds();*/

	//Sprites junto con la hitbox.
	chiwis.sprite.setPosition(chiwis.hitbox.getPosition().x, chiwis.hitbox.getPosition().y);
	sheguis.sprite.setPosition(sheguis.hitbox.getPosition().x, sheguis.hitbox.getPosition().y);
	soruya.sprite.setPosition(soruya.hitbox.getPosition().x, soruya.hitbox.getPosition().y);
	mindy.sprite.setPosition(mindy.hitbox.getPosition().x, mindy.hitbox.getPosition().y);
	bella.sprite.setPosition(bella.hitbox.getPosition().x, bella.hitbox.getPosition().y);
	manteca.sprite.setPosition(manteca.hitbox.getPosition().x, manteca.hitbox.getPosition().y);
	pushi.sprite.setPosition(pushi.hitbox.getPosition().x, pushi.hitbox.getPosition().y);
	muneca.sprite.setPosition(muneca.hitbox.getPosition().x, muneca.hitbox.getPosition().y);

	// Check item collision ************************************************************************
	displayItemPrompt = false;
	if (mPlayerCollider.intersects(mItemCollider) || mPlayerCollider.intersects(mItemArrowCollider)) {

		if (mItem.getPosition().x == 3070.f && mItem.getPosition().y == 2760.f) {
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
			if(cargandoItem){
				quitarVida = 0.f;
				mordidas = 0.f;
				mItemArrow.setPosition(-1000, -1000);
                mItem.setPosition(3070.f, 2760.f);
				mItem.setScale(1.7f, 1.7f);
                cargandoItem = false;
                PizzasEntregadas++;
            } else {
                cargandoItem = true;
                NuevaPosicion = rand() % 35;
				mItemArrow.setPosition(PosicionesItem[0][NuevaPosicion], PosicionesItem[1][NuevaPosicion]);
				mItemArrow.setScale(0.3f, 0.3f);
				mItem.setPosition(-1000, -1000);
            }
		}
	}


	cout << "x: " << mItemArrow.getPosition().x << std::endl;
	cout << "y: " << mItemArrow.getPosition().y << std::endl;
	cout << "\n";

	//Flecha**************************************
	if (mItem.getPosition().x == 3070.f && mItem.getPosition().y == 2760.f) {
		Flecha(xPlayer, yPlayer, mItem.getPosition().x, mItem.getPosition().y);
	}
	else {
		Flecha(xPlayer, yPlayer, mItemArrow.getPosition().x, mItemArrow.getPosition().y);
	}

	//Imprimir texto******************************
	this->ContadorPizzas(mPlayer.getPosition().x, mPlayer.getPosition().y, PizzasEntregadas, texto, m_font2);

	chiwis.checkMordidas(mordidas, quitarVida, mPlayerCollider);
	sheguis.checkMordidas(mordidas, quitarVida, mPlayerCollider);
	soruya.checkMordidas(mordidas, quitarVida, mPlayerCollider);
	bella.checkMordidas(mordidas, quitarVida, mPlayerCollider);
	pushi.checkMordidas(mordidas, quitarVida, mPlayerCollider);
	muneca.checkMordidas(mordidas, quitarVida, mPlayerCollider);
	mindy.checkMordidas(mordidas, quitarVida, mPlayerCollider);
	manteca.checkMordidas(mordidas, quitarVida, mPlayerCollider);


	/*if (ChiwisCollider.intersects(mPlayerCollider) ||
		SheguisCollider.intersects(mPlayerCollider)||
		SoruyaCollider.intersects(mPlayerCollider) ||
		BellaCollider.intersects(mPlayerCollider)  ||
		PushiCollider.intersects(mPlayerCollider)  ||
		MunecaCollider.intersects(mPlayerCollider) ||
		MindyCollider.intersects(mPlayerCollider)  ||
		MantecaCollider.intersects(mPlayerCollider))
	{
		Mordidas++;
		if (Mordidas > 0 && Mordidas < 120) 
			QuitarVida += 0.5f;
    }*/

	// Keep track of previous positions ************************************************************************
	sf::Vector2f previousPlayerPos = mPlayer.getPosition();
	sf::Vector2f previousChiwisPos = chiwis.hitbox.getPosition();
	sf::Vector2f previousSheguisPos = sheguis.hitbox.getPosition();
	sf::Vector2f previousSoruyaPos = soruya.hitbox.getPosition();
	sf::Vector2f previousMindyPos = mindy.hitbox.getPosition();
	sf::Vector2f previousBellaPos = bella.hitbox.getPosition();
	sf::Vector2f previousMantecaPos = manteca.hitbox.getPosition();
	sf::Vector2f previousPushiPos = pushi.hitbox.getPosition();
	sf::Vector2f previousMunecaPos = muneca.hitbox.getPosition();

	// Guardar Coordenadas del jugador en variables*************************************************************
	xPlayer = mPlayer.getPosition().x;
	yPlayer = mPlayer.getPosition().y;

	sheguis.followPlayer(xPlayer, yPlayer, 2000.f, 2100.f, deltaTime);
	soruya.followPlayer(xPlayer, yPlayer, 3000.f, 700.f, deltaTime);
	mindy.followPlayer(xPlayer, yPlayer, 1816.f, 1466.f, deltaTime);
	bella.followPlayer(xPlayer, yPlayer, 85.f, 790.f, deltaTime);
	manteca.followPlayer(xPlayer, yPlayer, 2366.f, 2800.f, deltaTime);
	pushi.followPlayer(xPlayer, yPlayer, 85.f, 1950.f, deltaTime);
	muneca.followPlayer(xPlayer, yPlayer, 1500.f, 2415.f, deltaTime);

	//float xSheguis = hitboxsheguis.getPosition().x;
	//float ySheguis = hitboxsheguis.getPosition().y;
	//Seguir(xPlayer, yPlayer, xSheguis, ySheguis, 2000, 2100, SheguisSpeed, hitboxsheguis, deltaTime);
	//
	//float xSoruya = hitboxsoruya.getPosition().x;
	//float ySoruya = hitboxsoruya.getPosition().y;
	//Seguir(xPlayer, yPlayer, xSoruya, ySoruya, 3000, 700, SoruyaSpeed, hitboxsoruya, deltaTime);

	//float xMindy = hitboxmindy.getPosition().x;
	//float yMindy = hitboxmindy.getPosition().y;
	//Seguir(xPlayer, yPlayer, xMindy, yMindy, 1816, 1466, MindySpeed, hitboxmindy, deltaTime);

	//float xBella = hitboxbella.getPosition().x;
	//float yBella = hitboxbella.getPosition().y;
	//Seguir(xPlayer, yPlayer, xBella, yBella, 85, 790, BellaSpeed, hitboxbella, deltaTime);

	//float xManteca = hitboxmanteca.getPosition().x;
	//float yManteca = hitboxmanteca.getPosition().y;
	//Seguir(xPlayer, yPlayer, xManteca, yManteca, 2366, 2800, MantecaSpeed, hitboxmanteca, deltaTime);

	//float xPushi = hitboxpushi.getPosition().x;
	//float yPushi = hitboxpushi.getPosition().y;
	//Seguir(xPlayer, yPlayer, xPushi, yPushi, 85, 1950, PushiSpeed, hitboxpushi, deltaTime);

	//float xMuneca = hitboxmuneca.getPosition().x;
	//float yMuneca = hitboxmuneca.getPosition().y;
	//Seguir(xPlayer, yPlayer, xMuneca, yMuneca, 1500, 2415, MunecaSpeed, hitboxmuneca, deltaTime);
	//**************************************************************************************************


	//*************CHIWIS******************************************************************************

	float dxchiwis = mPlayer.getPosition().x - chiwis.hitbox.getPosition().x;
	float dychiwis = mPlayer.getPosition().y - chiwis.hitbox.getPosition().y;
	float distancechiwis = sqrt(pow(dxchiwis, 2.f) + pow(dychiwis, 2.f));

	sf::Vector2f unitVectorchiwis(dxchiwis / distancechiwis, dychiwis / distancechiwis);
	if (distancechiwis <= RadioChiwis) {
		ChiwisSpeed = 250.f;
		sf::Vector2f velocitychiwis = unitVectorchiwis * (ChiwisSpeed);
		chiwis.hitbox.move(velocitychiwis * deltaTime.asSeconds());
	}
	else {
		ChiwisSpeed = 400.f;
		sf::Vector2f velocitychiwis = unitVectorchiwis * (ChiwisSpeed);
		chiwis.hitbox.move(velocitychiwis * deltaTime.asSeconds());
	}
	//*************************************************************************************************


	// Move player 
	mPlayer.move(movement * deltaTime.asSeconds());
	hitboxplayer.move(movement * deltaTime.asSeconds());



	// *************COLLISIONS*************************************************************************

	// Create Collidable object for the player and enemies
	Collidable playerCollidable(1, mPlayer.getGlobalBounds(), true);
	Collidable chiwisCollidable(1, chiwis.hitbox.getGlobalBounds(), true);
	Collidable sheguisCollidable(1, sheguis.hitbox.getGlobalBounds(), true);
	Collidable soruyaCollidable(1, soruya.hitbox.getGlobalBounds(), true);
	Collidable mindyCollidable(1, mindy.hitbox.getGlobalBounds(), true);
	Collidable bellaCollidable(1, bella.hitbox.getGlobalBounds(), true);
	Collidable mantecaCollidable(1, manteca.hitbox.getGlobalBounds(), true);
	Collidable pushiCollidable(1, pushi.hitbox.getGlobalBounds(), true);
	Collidable munecaCollidable(1, muneca.hitbox.getGlobalBounds(), true);

	// Check for collisions
	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(playerCollidable.m_bounds)) {
			mPlayer.setPosition(previousPlayerPos);
			hitboxplayer.setPosition(previousPlayerPos);

		}
	}
	checkCollision(objects, chiwisCollidable, chiwis.hitbox , 250.f, deltaTime);
	checkCollision(objects, sheguisCollidable, sheguis.hitbox, 250.f, deltaTime);
	checkCollision(objects, soruyaCollidable, soruya.hitbox, 250.f, deltaTime);
	checkCollision(objects, mindyCollidable, mindy.hitbox, 250.f, deltaTime);
	checkCollision(objects, bellaCollidable, bella.hitbox, 250.f, deltaTime);
	checkCollision(objects, mantecaCollidable, manteca.hitbox, 250.f, deltaTime);
	checkCollision(objects, pushiCollidable, pushi.hitbox, 250.f, deltaTime);
	checkCollision(objects, munecaCollidable, muneca.hitbox, 250.f, deltaTime);

	// Vida Player*************************************************************************************
	
	this->BarraVida(quitarVida, xPlayer, yPlayer);
	this->BarraVidaAux(xPlayer, yPlayer);

	//*************************************************************************************************
}

/*******************************************************************************************************************************************************************/

void Game::render()
{
	mWindow.clear();;
	mWindow.draw(background);
	mWindow.draw(objects);
	mWindow.draw(PizzaLogo);
    mWindow.draw(mItem);
	mWindow.draw(mPlayer);
	mWindow.draw(mItemArrow);
	//mWindow.draw(hitboxplayer);
	//mWindow.draw(hitboxchiwis);
	//mWindow.draw(hitboxsheguis);
	//mWindow.draw(hitboxsoruya);
	//mWindow.draw(hitboxmindy);

	if (displayItemPrompt) {
		mWindow.draw(prompt);
	}

	//mWindow.draw(hitboxbella);
	//mWindow.draw(hitboxmanteca);
	//mWindow.draw(hitboxpushi);
	//mWindow.draw(hitboxmuneca);
	mWindow.draw(vidaaux);
	mWindow.draw(vida);
	mWindow.draw(chiwis.sprite);
	mWindow.draw(sheguis.sprite);
	mWindow.draw(soruya.sprite);
	mWindow.draw(mindy.sprite);
	mWindow.draw(bella.sprite);
	mWindow.draw(manteca.sprite);
	mWindow.draw(pushi.sprite);
	mWindow.draw(muneca.sprite);
	mWindow.draw(arrow);
	mWindow.draw(fondotexto);
	mWindow.draw(texto);

	mWindow.display();

}
/*******************************************************************************************************************************************************************/

void Game::Initialize()
{
	// Initialize MainMenu 
	if (!m_font.loadFromFile("Fonts\\ka1.ttf"))
		cout << ("Error al cargar el font.");
	
	if (!m_font2.loadFromFile("Fonts\\font2.ttf"))
		cout << ("Error al cargar el font del item.");
	
	if (!m_menuBackground.loadFromFile("Images\\FondoMainMenu.png"))
		cout << ("Error al cargar el fondo del menu.");
	MainMenu mainMenu(m_font, m_menuBackground);

	// Item
	if (!mItemTexture.loadFromFile("Images\\PizzaBox.png"))
		cout << ("Error al cargar el archivo del Item.");
	mItem.setTexture(mItemTexture);
	mItem.setPosition(3070.f, 2760.f);
	mItem.setScale(1.7f, 1.7f);

	// Flecha del Item 
	if (!mItemArrowTexture.loadFromFile("Images\\PixelArrowRotated.png"))
		cout << ("Error al cargar el archivo del Item.");
	mItemArrow.setTexture(mItemArrowTexture);
	mItemArrow.setScale(0.3f, 0.3f);

	// Game Over
	if (!GameOverTex.loadFromFile("Images\\GameOver_.png"))
		cout << ("Error al cargar el archivo de game over.");
	GameOver.setTexture(GameOverTex);
	GameOver.setScale(1.5f, 1.5f);

	// Music 
	if (!music.openFromFile("Audios\\GORILLAvsHUMAN.wav"))
		cout << ("Error al cargar el audio.");
	music.setVolume(10.f);

	if (!menuMusic.openFromFile("Audios\\omairi.wav"))
		cout << ("Error al cargar el audio del menu.");
	menuMusic.setVolume(20.f);

	if (!deathSound.openFromFile("Audios\\death.wav"))
		cout << ("Error al cargar el audio de game over.");

	// Tilemap 
	if (!background.load("Images\\Tileset.png", sf::Vector2u(48, 48)))
		cout << ("Error al cargar el mapa.");

	// Collision objects
	if (!objects.load("Images\\Tileset.png", sf::Vector2u(48, 48)))
		cout << ("Error al cargar los objetos del mapa.");


	// Pizza logo in restaurant
	if (!PizzaLogoTex.loadFromFile("Images\\Pizza.png"))
		cout << ("Error al cargar el archivo de la pizza");

	// Player 
	if (!mTexture.loadFromFile("Images\\Robot.png"))
		cout << ("Error al cargar el archivo.");
	m_playerRect.left = 0;
	m_playerRect.top = 0;
	m_playerRect.width = 320;
	m_playerRect.height = 320;
	mPlayer.setTexture(mTexture);
	mPlayer.setTextureRect(m_playerRect);
	mPlayer.setPosition(2500.f, 2500.f);
	mPlayer.setScale(0.18f, 0.18f);


	// Textura del Item 
	if (!mItemTexture.loadFromFile("Images\\PizzaBox.png"))
		cout << ("Error al cargar el archivo del Item.");
	mItem.setTexture(mItemTexture);
	mItem.setPosition(3070.f, 2760.f);
	mItem.setScale(1.7f, 1.7f);

	if (!mItemArrowTexture.loadFromFile("Images\\PixelArrowRotated.png"))
		cout << ("Error al cargar el archivo del Item.");
	mItemArrow.setTexture(mItemArrowTexture);
	mItem.setPosition(-1000, -1000);


	// Textura Chiwis
	if (!chiwis.texture.loadFromFile("Images\\Mascotas.png")) 
		cout << ("Error al cargar la textura de chiwis.");
	chiwis.texRect.left = 0;
	chiwis.texRect.width = 36;
	chiwis.texRect.height = 47;
	chiwis.sprite.setTexture(chiwis.texture);
	chiwis.sprite.setTextureRect(chiwis.texRect);
	chiwis.sprite.setPosition(3000.f, 700.f);
	chiwis.sprite.setScale(1.5f, 1.5f);

	sf::FloatRect chiwisRect = chiwis.sprite.getGlobalBounds();
	float chiwisWidth = chiwisRect.width;
	float chiwisHeight = chiwisRect.height;

	// Textura Sheguis 
	if (!sheguis.texture.loadFromFile("Images\\Mascotas.png")) 
		cout << ("Error al cargar la textura de sheguis.");
	sheguis.texRect.left = 0;
	sheguis.texRect.width = 36;
	sheguis.texRect.height = 47;
	sheguis.sprite.setTexture(sheguis.texture);
	sheguis.sprite.setTextureRect(sheguis.texRect);
	sheguis.sprite.setPosition(2000.f, 2100.f);
	sheguis.sprite.setScale(1.5f, 1.5f);

	sf::FloatRect sheguisRect = sheguis.sprite.getGlobalBounds();
	float sheguisWidth = sheguisRect.width;
	float sheguisHeight = sheguisRect.height;

	// Textura Soruya 
	if (!soruya.texture.loadFromFile("Images\\Mascotas.png")) 
		cout << ("Error al cargar la textura de soruya.");
	soruya.texRect.left = 156;
	soruya.texRect.width = 36;
	soruya.texRect.height = 47;
	soruya.sprite.setTexture(soruya.texture);
	soruya.sprite.setTextureRect(soruya.texRect);
	soruya.sprite.setPosition(3000.f, 700.f);
	soruya.sprite.setScale(1.5f, 1.5f);

	sf::FloatRect soruyaRect = soruya.sprite.getGlobalBounds();
	float soruyaWidth = soruyaRect.width;
	float soruyaHeight = soruyaRect.height;

	// Textura Mindy
	if (!mindy.texture.loadFromFile("Images\\Mascotas.png"))
		cout << ("Error al cargar la textura de mindy.");
	mindy.texRect.left = 156;
	mindy.texRect.width = 36;
	mindy.texRect.height = 47;
	mindy.sprite.setTexture(mindy.texture);
	mindy.sprite.setTextureRect(mindy.texRect);
	mindy.sprite.setPosition(1816.f, 1466.f);
	mindy.sprite.setScale(1.5f, 1.5f);

	sf::FloatRect mindyRect = mindy.sprite.getGlobalBounds();
	float mindyWidth = mindyRect.width;
	float mindyHeight = mindyRect.height;

	// Textura Bella
	if (!bella.texture.loadFromFile("Images\\Mascotas.png"))
		cout << ("Error al cargar la textura de bella.");
	bella.texRect.left = 468;
	bella.texRect.width = 36;
	bella.texRect.height = 47;
	bella.sprite.setTexture(bella.texture);
	bella.sprite.setTextureRect(bella.texRect);
	bella.sprite.setPosition(85.f, 790.f);
	bella.sprite.setScale(1.5f, 1.5f);

	sf::FloatRect bellaRect = bella.sprite.getGlobalBounds();
	float bellaWidth = bellaRect.width;
	float bellaHeight = bellaRect.height;

	// Textura Manteca 
	if (!manteca.texture.loadFromFile("Images\\Mascotas.png"))
		cout << ("Error al cargar la textura de manteca.");
	manteca.texRect.left = 312;
	manteca.texRect.width = 36;
	manteca.texRect.height = 47;
	manteca.sprite.setTexture(manteca.texture);
	manteca.sprite.setTextureRect(manteca.texRect);
	manteca.sprite.setPosition(2366.f, 2800.f);
	manteca.sprite.setScale(1.5f, 1.5f);

	sf::FloatRect mantecaRect = manteca.sprite.getGlobalBounds();
	float mantecaWidth = mantecaRect.width;
	float mantecaHeight = mantecaRect.height;

	// Textura Pushi 
	if (!pushi.texture.loadFromFile("Images\\Mascotas.png")) 
		cout << ("Error al cargar la textura de pushi.");
	pushi.texRect.left = 312;
	pushi.texRect.width = 36;
	pushi.texRect.height = 47;
	pushi.sprite.setTexture(pushi.texture);
	pushi.sprite.setTextureRect(pushi.texRect);
	pushi.sprite.setPosition(85.f, 1950.f);
	pushi.sprite.setScale(1.5f, 1.5f);

	sf::FloatRect pushiRect = pushi.sprite.getGlobalBounds();
	float pushiWidth = pushiRect.width;
	float pushiHeight = pushiRect.height;

	// Textura Muneca 
	if (!muneca.texture.loadFromFile("Images\\Mascotas.png"))
		cout << ("Error al cargar la textura de muneca.");
	muneca.texRect.left = 468;
	muneca.texRect.width = 36;
	muneca.texRect.height = 47;
	muneca.sprite.setTexture(muneca.texture);
	muneca.sprite.setTextureRect(muneca.texRect);
	muneca.sprite.setPosition(1500.f, 2415.f);
	muneca.sprite.setScale(1.5f, 1.5f);

	sf::FloatRect munecaRect = muneca.sprite.getGlobalBounds();
	float munecaWidth = munecaRect.width;
	float munecaHeight = munecaRect.height;

	// Texto del item 
	prompt.setFont(m_font2);

	// Hitboxes 
	this->HitBoxPlayer();
	chiwis.setHitbox(3000.f, 700.f, chiwisWidth, chiwisHeight);
	sheguis.setHitbox(2000.f, 2100.f, sheguisWidth, sheguisHeight);
	soruya.setHitbox(3000.f, 700.f, soruyaWidth, soruyaHeight);
	mindy.setHitbox(1816.f, 1466.f, mindyWidth, mindyHeight);
	bella.setHitbox(85.f, 790.f, bellaWidth, bellaHeight);
	manteca.setHitbox(2366.f, 2800.f, mantecaWidth, mantecaHeight);
	pushi.setHitbox(85.f, 1950.f, pushiWidth, pushiHeight);
	muneca.setHitbox(1500.f, 2415.f, munecaWidth, munecaHeight);


	// Crear arreglo y empezar semilla 
	MakeArray();
	srand(time(NULL));
}

//*******************************************************************************************************************************************************************

void Game::checkCollision(const SurfaceObjects& objects, const Collidable& petCollidable, sf::RectangleShape& petHitbox, const float petSpeed, sf::Time deltaTime)
{
	for (auto& collidable : objects.collidables) {
		if (collidable.m_bounds.intersects(petCollidable.m_bounds)) {
			// Handle collision
			sf::FloatRect intersection;
			if (petHitbox.getGlobalBounds().intersects(collidable.getBounds(), intersection)) {
				// Calculate shortest distance to move hitbox away from intersection
				sf::Vector2f direction = petHitbox.getPosition() - sf::Vector2f(intersection.left + intersection.width / 2, intersection.top + intersection.height / 2);
				float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction /= distance;
				sf::Vector2f size = petHitbox.getSize();
				float radius = std::sqrt(size.x * size.x + size.y * size.y) / 2.f;

				// Calculate distance to move enemy away from intersection point
				float overlapX = (radius - (intersection.width / 2.f)) * direction.x;
				float overlapY = (radius - (intersection.height / 2.f)) * direction.y;

				// Add randomness to new position calculation
				sf::Vector2f randOffset = sf::Vector2f(((rand() % 51) - 25) * 0.2f, ((rand() % 51) - 25) * 0.2f);
				sf::Vector2f newPosition = petHitbox.getPosition() + sf::Vector2f(overlapX, overlapY) + randOffset;

				// Adjust speed based on distance to collision point
				float speed = petSpeed * (distance / radius);
				sf::Vector2f velocity = direction * speed;
				petHitbox.move(velocity * deltaTime.asSeconds());
				break;
			}
		}
	}
}

//*******************************************************************************************************************************************************************

void Game::ContadorPizzas(float xPlayer, float yPlayer, int cantidad_pizzas, sf::Text& texto, sf::Font& fuente) {

	this->fondotexto.setPosition(xPlayer - 450.f, yPlayer - 450.f);
	this->fondotexto.setSize(sf::Vector2f(260.f, 30.f));
	this->fondotexto.setFillColor(sf::Color::Blue);
	this->fondotexto.setOutlineColor(sf::Color::Black);
	this->fondotexto.setOutlineThickness(4.f);
	this->texto.setFont(fuente); // "fuente" es el objeto de la fuente que quieres utilizar
	this->texto.setCharacterSize(20); // ajusta el tamaño del texto según tus necesidades
	this->texto.setPosition(xPlayer - 450.f, yPlayer - 450.f);
	this->texto.setString("Pizzas entregadas: " + std::to_string(cantidad_pizzas));
}

void Game::Flecha(float xPlayer, float yPlayer, float xItem, float yItem) {

	float dx = xItem - xPlayer;
	float dy = yItem - yPlayer;
	float angle = atan2(dy, dx) * 180 / 3.141592 - 90; // calcular el �ngulo en grados
	this->arrow.setRotation(angle); // rotar la flecha
	float arrowOffset = -50.f; // ajusta esto para que la flecha est� en la posici�n correcta

	// establecer los puntos de la flecha en relaci�n con la posici�n del jugador
	this->arrow.setPointCount(3);
	this->arrow.setPoint(0, sf::Vector2f(xPlayer, yPlayer));
	this->arrow.setPoint(1, sf::Vector2f(xPlayer - 10.f, yPlayer - 10.f));
	this->arrow.setPoint(2, sf::Vector2f(xPlayer + 10.f, yPlayer - 10.f));
	this->arrow.setFillColor(sf::Color::Yellow);

	// ajustar el origen de la flecha para que est� en la punta superior
	this->arrow.setOrigin(xPlayer, yPlayer - 20.f);

	// ajustar la escala de la flecha
	this->arrow.setScale(1.f,1.f); // ajusta la escala seg�n lo necesites

	// enmarcar el contorno de la flecha de negro
	this->arrow.setOutlineThickness(2.f);
	this->arrow.setOutlineColor(sf::Color::Black);

	// calcular la posici�n del centro del c�rculo
	float circleRadius = 80.f; // ajusta el radio del c�rculo seg�n lo necesites
	sf::Vector2f circleCenter(xPlayer + 15.f, yPlayer + 20.f);

	// calcular la posici�n de la flecha en el borde del c�rculo
	float angleRadians = (angle + 90) * 3.141592 / 180; // convertir el �ngulo a radianes y ajustar para la orientaci�n de la flecha
	sf::Vector2f arrowPosition(cos(angleRadians) * circleRadius, sin(angleRadians) * circleRadius);

	// ajustar la posici�n de la flecha en funci�n del centro del c�rculo
	arrowPosition += circleCenter;

	// establecer la posici�n de la flecha
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
//
//void Game::HitBoxChiwis()
//{
//	this->hitboxchiwis.setPosition(3000.f, 700.f);
//	this->hitboxchiwis.setSize(sf::Vector2f(ChiwisWidth, ChiwisHeight));
//	this->hitboxchiwis.setFillColor(sf::Color::Transparent);
//	this->hitboxchiwis.setOutlineColor(sf::Color::Transparent);
//	this->hitboxchiwis.setOutlineThickness(6.f);
//}
//
//void Game::HitBoxSheguis()
//{
//	this->hitboxsheguis.setPosition(2000.f, 2100.f);
//	this->hitboxsheguis.setSize(sf::Vector2f(SheguisWidth, SheguisHeight));
//	this->hitboxsheguis.setFillColor(sf::Color::Transparent);
//	this->hitboxsheguis.setOutlineColor(sf::Color::Transparent);
//	this->hitboxsheguis.setOutlineThickness(6.f);
//}
//
//void Game::HitBoxSoruya()
//{
//	this->hitboxsoruya.setPosition(3000.f, 700.f);
//	this->hitboxsoruya.setSize(sf::Vector2f(SoruyaWidth, SoruyaHeight));
//	this->hitboxsoruya.setFillColor(sf::Color::Transparent);
//	this->hitboxsoruya.setOutlineColor(sf::Color::Transparent);
//	this->hitboxsoruya.setOutlineThickness(6.f);
//}
//
//void Game::HitBoxMindy()
//{
//	this->hitboxmindy.setPosition(1816.f, 1466.f);
//	this->hitboxmindy.setSize(sf::Vector2f(MindyWidth, MindyHeight));
//	this->hitboxmindy.setFillColor(sf::Color::Transparent);
//	this->hitboxmindy.setOutlineColor(sf::Color::Transparent);
//	this->hitboxmindy.setOutlineThickness(6.f);
//}
//
//
//void Game::HitBoxBella()
//{
//	this->hitboxbella.setPosition(85.f, 790.f);
//	this->hitboxbella.setSize(sf::Vector2f(BellaWidth, BellaHeight));
//	this->hitboxbella.setFillColor(sf::Color::Transparent);
//	this->hitboxbella.setOutlineColor(sf::Color::Transparent);
//	this->hitboxbella.setOutlineThickness(6.f);
//}
//
//void Game::HitBoxManteca()
//{
//	this->hitboxmanteca.setPosition(2366.f, 2800.f);
//	this->hitboxmanteca.setSize(sf::Vector2f(MantecaWidth, MantecaHeight));
//	this->hitboxmanteca.setFillColor(sf::Color::Transparent);
//	this->hitboxmanteca.setOutlineColor(sf::Color::Transparent);
//	this->hitboxmanteca.setOutlineThickness(6.f);
//}
//
//void Game::HitBoxPushi()
//{
//	this->hitboxpushi.setPosition(85.f, 1950.f);
//	this->hitboxpushi.setSize(sf::Vector2f(PushiWidth, PushiHeight));
//	this->hitboxpushi.setFillColor(sf::Color::Transparent);
//	this->hitboxpushi.setOutlineColor(sf::Color::Transparent);
//	this->hitboxpushi.setOutlineThickness(6.f);
//}
//
//void Game::HitBoxMuneca()
//{
//	this->hitboxmuneca.setPosition(1500.f, 2415.f);
//	this->hitboxmuneca.setSize(sf::Vector2f(MunecaWidth, MunecaHeight));
//	this->hitboxmuneca.setFillColor(sf::Color::Transparent);
//	this->hitboxmuneca.setOutlineColor(sf::Color::Transparent);
//	this->hitboxmuneca.setOutlineThickness(6.f);
//}


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

//void Game::Seguir(float xPlayer, float yPlayer, float xMascota, float yMascota, float Pox, float Poy, float Speed, sf::RectangleShape& hitboxmascota, sf::Time deltaTime) {
//	float dx = xPlayer - xMascota;
//	float dy = yPlayer - yMascota;
//	float distance = sqrt(pow(dx, 2.f) + pow(dy, 2.f));
//
//	float dxaux = Pox - xMascota;
//	float dyaux = Poy - yMascota;
//	float distanceaux = sqrt(pow(dxaux, 2.f) + pow(dyaux, 2.f));
//
//	sf::Vector2f unitVector(dx / distance, dy / distance);
//	sf::Vector2f unitVectoraux(dxaux / (distanceaux + 0.1), dyaux / (distanceaux + 0.1));
//
//	sf::Vector2f velocity = unitVector * (Speed);
//	sf::Vector2f velocityaux = unitVectoraux * (Speed);
//
//	if (distance <= RadioDetected && distanceaux <= RadioDetected) {
//		hitboxmascota.move(velocity * deltaTime.asSeconds());
//	}
//	else {
//		hitboxmascota.move(velocityaux * deltaTime.asSeconds());
//	}
//}
//
//float Game::Angulo(float xPlayer, float yPlayer, float xMascota, float yMascota, float Pox, float Poy, const float Speed) {
//	float dx = xPlayer - xMascota;
//	float dy = yPlayer - yMascota;
//	float distance = sqrt(pow(dx, 2.f) + pow(dy, 2.f));
//
//	float dxaux = Pox - xMascota;
//	float dyaux = Poy - yMascota;
//	float distanceaux = sqrt(pow(dxaux, 2.f) + pow(dyaux, 2.f));
//
//	sf::Vector2f unitVector(dx / distance, dy / distance);
//	sf::Vector2f unitVectoraux(dxaux / (distanceaux + 0.1), dyaux / (distanceaux + 0.1));
//
//	sf::Vector2f velocity = unitVector * (Speed);
//	sf::Vector2f velocityaux = unitVectoraux * (Speed);
//
//	if (distance <= RadioDetected && distanceaux <= RadioDetected) {
//		float angle = atan2(velocity.y, velocity.x) * 180 / 3.141592 + 180.f;
//		return angle ;
//	}
//	else {
//		float angle = atan2(velocityaux.y, velocityaux.x) * 180/3.141592 + 180.f;
//		return angle;
//	}
//}

float Game::AnguloChiwis(float xPlayer, float yPlayer, float xMascota, float yMascota, const float Speed) {
	float dx = xPlayer - xMascota;
	float dy = yPlayer - yMascota;
	float distance = sqrt(pow(dx, 2.f) + pow(dy, 2.f));
	sf::Vector2f unitVector(dx / distance, dy / distance);
	sf::Vector2f velocity = unitVector * (Speed);
	float angle = atan2(velocity.y, velocity.x) * 180 / 3.141592 + 180.f;
	return angle;
	
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