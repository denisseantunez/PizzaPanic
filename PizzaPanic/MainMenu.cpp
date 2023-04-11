
#include "MainMenu.h"


MainMenu::MainMenu(sf::Font& font, sf::Texture& backgroundTexture)
		: m_font(font)
		, m_menuBackground(backgroundTexture)
{
	// Set up menu items
	
	// Title
	sf::Text Title("PIZZA PANIC", m_font);
	Title.setCharacterSize(55);
	Title.setPosition(210, 30);
	m_menuItems.emplace_back(std::move(Title));

	// Play button
	sf::Text playText("Play", m_font);
	playText.setPosition(100, 400);
	m_menuItems.emplace_back(std::move(playText));

	// Credits button
	sf::Text creditsText("Credits", m_font);
	creditsText.setPosition(100, 430);
	m_menuItems.emplace_back(std::move(creditsText));

	// Quit button
	sf::Text quitText("Quit", m_font);
	quitText.setPosition(100, 460);
	m_menuItems.emplace_back(std::move(quitText));

}

void MainMenu::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			// Check if any menu option was clicked
			for (const auto& menuItem : m_menuItems) {
				if (menuItem.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {

					if (menuItem.getString() == "Play") {
						m_selectedOption = Option::Play;
					}
					else if (menuItem.getString() == "Credits") {
						m_selectedOption = Option::Credits;
					}
					else if (menuItem.getString() == "Quit") {
						m_selectedOption = Option::Quit;
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


