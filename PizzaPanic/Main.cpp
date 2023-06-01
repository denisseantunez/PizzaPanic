
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
		game.mItem.setPosition(3070.f, 2760.f);
		game.player.sprite.setPosition(game.player.initialX, game.player.initialY);
		game.mItem.setScale(1.7f, 1.7f);
		game.chiwis.hitbox.setPosition(3000.f, 700.f);
		game.manteca.hitbox.setPosition(2366.f, 2800.f);

		game.mView.reset(sf::FloatRect(0, 0, game.mWindow.getSize().x, game.mWindow.getSize().y));
		game.mWindow.setView(game.mView);

		game.menuMusic.play();
		game.menuMusic.setLoop(true);
		game.showMainMenu();

		// If Play button is clicked, start the game
		if (game.mainMenu.getSelectedOption() == MainMenu::Option::Jugar) {

			// Play game music
			game.menuMusic.stop();
			game.music.play();
			game.music.setLoop(true);

			// Keep track of the player's initial position
			sf::Vector2f previousPlayerPos = game.player.sprite.getPosition();

			sf::Clock clock;

			sf::Time timeSinceLastUpdate = sf::Time::Zero;
			while (game.mWindow.isOpen()) {
				game.processEvents();
				timeSinceLastUpdate += clock.restart();
				while (timeSinceLastUpdate > TimePerFrame) {
					timeSinceLastUpdate -= TimePerFrame;
					game.processEvents();
					game.update(TimePerFrame);
				}
				game.render();
				// If player dies
				if (game.bites >= 60) {
					game.deliveredPizzas = 0;
					game.mItem.setPosition(3070.f, 2760.f);
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
	} while (game.mainMenu.getSelectedOption() == MainMenu::Option::Jugar);
	
}