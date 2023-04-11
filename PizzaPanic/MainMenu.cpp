
#include "MainMenu.h"


MainMenu::MainMenu(sf::Font& font, sf::Texture& backgroundTexture)
		: m_font(font)
		, m_backgroundTexture(backgroundTexture)
{
	// Set up menu items

	// Play button
	sf::Text playText("Play", m_font);
	playText.setPosition(100, 100);
	m_menuItems.emplace_back(std::move(playText));

	// Credits button
	sf::Text creditsText("Credits", m_font);
	creditsText.setPosition(100, 125);
	m_menuItems.emplace_back(std::move(creditsText));

	// Quit button
	sf::Text quitText("Quit", m_font);
	quitText.setPosition(100, 150);
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
	sf::Sprite background(m_backgroundTexture);
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


