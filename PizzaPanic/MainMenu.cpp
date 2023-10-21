#include "MainMenu.h"
#include <vector>

/*******************************************************************************************************************************************************************/

MainMenu::MainMenu(sf::Font& font, sf::Texture& backgroundTexture)
	: m_font(font)
	, m_menuBackground(backgroundTexture)
{
	// Menu Items

	// Title
	sf::Text TitleShadow("PIZZA PANIC", m_font);
	TitleShadow.setCharacterSize(55);
	TitleShadow.setPosition(170, 30);
	TitleShadow.setStyle(sf::Text::Bold);
	TitleShadow.setFillColor(sf::Color::Black);
	m_menuItems.__emplace_back(std::move(TitleShadow));

	sf::Text Title("PIZZA PANIC", m_font);
	Title.setCharacterSize(55);
	Title.setPosition(173, 33);
	Title.setStyle(sf::Text::Bold);
	Title.setFillColor(sf::Color::Red);
	m_menuItems.__emplace_back(std::move(Title));
;
	// Play Button
	sf::RectangleShape playButton;
	playButton.setSize(sf::Vector2f(328, 40));
	playButton.setOutlineColor(sf::Color::Red);
	playButton.setOutlineThickness(2);
	playButton.setPosition(240, 300);
	playButton.setFillColor(sf::Color::White);
	m_menuButtons.__emplace_back(std::move(playButton));

	sf::Text playText("Jugar", m_font);
	playText.setFillColor(sf::Color::Black);
	playText.setPosition(335, 300);
	m_menuItems.__emplace_back(std::move(playText));


	// Instructions Button
	sf::RectangleShape instructionsButton;
	instructionsButton.setSize(sf::Vector2f(328, 40));
	instructionsButton.setOutlineColor(sf::Color::Red);
	instructionsButton.setOutlineThickness(2);
	instructionsButton.setPosition(240, 350);
	instructionsButton.setFillColor(sf::Color::White);
	m_menuButtons.__emplace_back(std::move(instructionsButton));

	sf::Text instructionsText("Instrucciones", m_font);
	instructionsText.setFillColor(sf::Color::Black);
	instructionsText.setPosition(250, 350);
	m_menuItems.__emplace_back(std::move(instructionsText));

	// Credits Button
	sf::RectangleShape creditsButton;
	creditsButton.setSize(sf::Vector2f(328, 40));
	creditsButton.setOutlineColor(sf::Color::Red);
	creditsButton.setOutlineThickness(2);
	creditsButton.setPosition(240, 400);
	creditsButton.setFillColor(sf::Color::White);
	m_menuButtons.__emplace_back(std::move(creditsButton));

	sf::Text creditsText("Creditos", m_font);
	creditsText.setFillColor(sf::Color::Black);
	creditsText.setPosition(310, 400);
	m_menuItems.__emplace_back(std::move(creditsText));

	// Quit Button
	sf::RectangleShape quitButton;
	quitButton.setSize(sf::Vector2f(328, 40));
	quitButton.setOutlineColor(sf::Color::Red);
	quitButton.setOutlineThickness(2);
	quitButton.setPosition(240, 450);
	quitButton.setFillColor(sf::Color::White);
	m_menuButtons.__emplace_back(std::move(quitButton));

	sf::Text quitText("Salir", m_font);
	quitText.setFillColor(sf::Color::Black);
	quitText.setPosition(345, 450);
	m_menuItems.__emplace_back(std::move(quitText));

	if (m_selectedOption == Option::Instrucciones || m_selectedOption == Option::Creditos) {
		// Go Back Button
		sf::RectangleShape backButton;
		backButton.setSize(sf::Vector2f(230, 40));
		backButton.setOutlineColor(sf::Color::Red);
		backButton.setOutlineThickness(2);
		backButton.setPosition(500, 520);
		backButton.setFillColor(sf::Color::White);
		m_menuButtons.__emplace_back(std::move(backButton));

		sf::Text backText("Regresar", m_font);
		backText.setFillColor(sf::Color::Black);
		backText.setPosition(500, 520);
		m_menuItems.__emplace_back(std::move(backText));
	}

}

/*******************************************************************************************************************************************************************/

void MainMenu::handleEvent(sf::Event event)
{
	
	if (event.type == sf::Event::MouseButtonPressed) {
		m_selectedOption = Option::Default;
		if (event.mouseButton.button == sf::Mouse::Left) {
			// Check if any menu option was clicked
			for (const auto& menuItem : m_menuItems) {
				if (menuItem.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {

					if (menuItem.getString() == "Jugar") {
						m_selectedOption = Option::Jugar;
					}
					else if (menuItem.getString() == "Instrucciones") {
						m_selectedOption = Option::Instrucciones; 

					}
					else if (menuItem.getString() == "Creditos") {
						m_selectedOption = Option::Creditos;
					}
					else if (menuItem.getString() == "Salir") {
						m_selectedOption = Option::Salir;
					}
					else if (menuItem.getString() == "Regresar") {
						m_selectedOption = Option::Regresar;
						// Erase Go Back Button from vector
						m_menuItems.pop_back();
						m_menuButtons.pop_back();
					}
					return;
				}
			}
		}
	}
}

/*******************************************************************************************************************************************************************/

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw background texture
	sf::Sprite background(m_menuBackground);
	target.draw(background);


	if (m_selectedOption == Option::Instrucciones || m_selectedOption == Option::Creditos) {
		// Boton de Regresar
		sf::RectangleShape backButton;
		backButton.setSize(sf::Vector2f(230, 40));
		backButton.setOutlineColor(sf::Color::Red);
		backButton.setOutlineThickness(2);
		backButton.setPosition(458, 530);
		backButton.setFillColor(sf::Color::White);
		target.draw(backButton);

		sf::Text backText("Regresar", m_font);
		backText.setFillColor(sf::Color::Black);
		backText.setPosition(468, 530);
		target.draw(backText);
	}

	// Draw menu buttons
	for (const auto& menuButton : m_menuButtons)
	{
		target.draw(menuButton);
	}

	// Draw menu options
	for (const auto& menuItem : m_menuItems)
	{
		target.draw(menuItem);
	}

	// Instructions
	if (m_selectedOption == Option::Instrucciones) {
		sf::Texture instructionsTexture;
		instructionsTexture.loadFromFile("Images\\Instrucciones.png");
		sf::Sprite Instructions(instructionsTexture);
		Instructions.setPosition(30, 8);
		Instructions.setScale(0.85f, 0.85f);

		target.draw(Instructions);

	}

	// Credits
	if (m_selectedOption == Option::Creditos) {
		sf::Texture creditsTexture;
		creditsTexture.loadFromFile("Images\\Creditos.png");
		sf::Sprite Credits(creditsTexture);
		Credits.setPosition(30, 8);
		Credits.setScale(0.85f, 0.85f);

		target.draw(Credits);

	}

}

/*******************************************************************************************************************************************************************/

MainMenu::Option MainMenu::getSelectedOption() const
{
	return m_selectedOption;
}

/*******************************************************************************************************************************************************************/

void MainMenu::resetSelectedOption()
{
	m_selectedOption = Option::Default;
}

/*******************************************************************************************************************************************************************/


