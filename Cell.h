#pragma once
#include "sdk.h"

class Cell
{
public:
	Cell(sf::Vector2i gridPosition);
	~Cell();

	bool isAlive();
	void die();
	void born();
	sf::Vector2i gridPosition();
	void setScreenRect(sf::FloatRect screenRect);
	sf::FloatRect getScreenRect();

	std::vector<Cell> neighbours;

	void bornNeighbours();

	void revealGridPosition();

	int ID = -99;

	int aliveNeighbours;

private:
	sf::Vector2i _gridPosition;
	bool _alive = false;
	sf::FloatRect _screenRect;

};

enum {
	topLeft,
	left,
	botLeft,
	top,
	bot,
	topRight,
	right,
	botRight
};

