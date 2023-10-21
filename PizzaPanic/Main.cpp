
#include "Game.h"


int main()
{
	Game game;
	
	do {
		// Initialize variables
		game.mainMenu.resetSelectedOption();
		game.processEvents();
		game.bites = 0.f;
		game.quitarVida = 0.f;
		game.mItem.setTexture(game.mItemTexture);
		game.mItem.setPosition(1436.f, 1388.f);
		game.player.sprite.setPosition(game.player.initialX, game.player.initialY);
		game.mItem.setScale(1.7f, 1.7f);

		// Open the window
		game.mView.reset(sf::FloatRect(0, 0, game.mWindow.getSize().x, game.mWindow.getSize().y));
		game.mWindow.setView(game.mView);

		// Playing music and showing Main Menu
		//game.menuMusic.play();
		//game.menuMusic.setLoop(true);
		game.showMainMenu();

		// If Play button is clicked, start the game
		if (game.mainMenu.getSelectedOption() == MainMenu::Option::Jugar) {

			// Play game music
			//game.menuMusic.stop();
			//game.music.play();
			game.music.setLoop(true);

			//Initializing time
			sf::Clock clock;

			sf::Time timeSinceLastUpdate = sf::Time::Zero;

			while (game.mWindow.isOpen()) {
				game.processEvents();
				timeSinceLastUpdate += clock.restart();

				while (timeSinceLastUpdate > TimePerFrame) {
					timeSinceLastUpdate -= TimePerFrame;
					//Updates everything that happens in the game.
					game.processEvents();
					game.update(TimePerFrame);
				}

				//Drawing sprites.
				game.render();

				// If player dies, reseting everything.
				if (game.bites >= 60) {
					game.clock2.restart();
					game.deliveredPizzas = 0;
					game.mItem.setPosition(1436.f, 1388.f);
					game.cargandoItem = false;
					game.music.stop();
					game.deathSound.play();
					game.deathSound.setLoop(true);
					game.gameOver.setPosition(game.mView.getCenter().x - 460.f, game.mView.getCenter().y - 500.f);
					game.mWindow.clear();
					game.mWindow.draw(game.gameOver);
					game.mWindow.display();
					std::this_thread::sleep_for(std::chrono::seconds(2));
					game.deathSound.stop();
					break;
				}
			}
		}
	} while (game.mainMenu.getSelectedOption() != MainMenu::Option::Salir && game.mWindow.isOpen());
<<<<<<< HEAD
=======
	
>>>>>>> f64cd4e60f18bd765ffb823f75569ddaccfdc993
}