#pragma once
#include "sdk.h"

class Label
{
public:
	Label(std::string fontName, int size, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Color clr = sf::Color::Black);
	void setString(std::string s);

	void render(sf::RenderWindow* window);
	sf::Font _font;
	sf::Text _text;

private:

};

