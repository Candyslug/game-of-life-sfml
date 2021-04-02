#pragma once
#include "sdk.h"


class Window
{
public:
	Window(std::string title, sf::Vector2i dimensions);
	~Window();
	void initRenderWindow();
	void close();
	void update();
private:
	sf::RenderWindow* _window;
	sf::Vector2i _dimensions;
	std::string _title;
};

