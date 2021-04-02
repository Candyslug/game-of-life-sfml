#include "Label.h"

Label::Label(std::string fontName, int size, sf::Vector2f pos, sf::Color clr) {

	if (!this->_font.loadFromFile(fontName)) {}

	this->_text;
	this->_text.setFont(this->_font);
	this->_text.setCharacterSize(size);
	this->_text.setPosition(pos);
	this->_text.setFillColor(clr);
}

void Label::setString(std::string s) {
	this->_text.setString(s);
}

void Label::render(sf::RenderWindow* window) {
	window->draw(this->_text);
}

