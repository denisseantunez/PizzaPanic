
#include "MainMenu.h"


MainMenu::MainMenu(sf::Font& font, sf::Texture& backgroundTexture)
		: m_font(font)
		, m_menuBackground(backgroundTexture)
{
	// Items del menu
	
	// Título
	sf::Text Title("PIZZA PANIC", m_font);
	Title.setCharacterSize(55);
	Title.setPosition(170, 30);
	Title.setStyle(sf::Text::Bold);
	Title.setFillColor(sf::Color::Red);
	m_menuItems.emplace_back(std::move(Title));

	// Botón de jugar
	sf::Text playText("Jugar", m_font);
	playText.setPosition(330, 300);
	m_menuItems.emplace_back(std::move(playText));

	// Botón de instrucciones
	sf::Text instructionsText("Instrucciones", m_font);
	instructionsText.setPosition(250, 350);
	m_menuItems.emplace_back(std::move(instructionsText));

	// Botón de créditos
	sf::Text creditsText("Creditos", m_font);
	creditsText.setPosition(300, 400);
	m_menuItems.emplace_back(std::move(creditsText));

	// Botón de Salir
	sf::Text quitText("Salir", m_font);
	quitText.setPosition(335, 450);
	m_menuItems.emplace_back(std::move(quitText));

}

void MainMenu::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed) {
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
					return;
				}
			}
		}
	}
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw background texture
	sf::Sprite background(m_menuBackground);
	target.draw(background);

	// Draw menu options
	for (const auto& menuItem : m_menuItems)
	{
		target.draw(menuItem);
	}
}

MainMenu::Option MainMenu::getSelectedOption() const
{
	return m_selectedOption;
}


