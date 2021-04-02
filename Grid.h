#pragma once
#include "sdk.h"
#include "Cell.h"

class Grid
{
public:
	Grid(sf::RenderWindow* window);
	~Grid();
	void init();
	void initCells();
	void initCellNeighbours();
	void render();
	void drawCells();
	void drawGrid();
	void drawMenu();
	void update();
	void updateCells();
	Cell getCell(sf::Vector2i gridPosition);
	void runSimulation();
	void stopSimulation();
	void pauseSimulation();
	int _cellAmount;
	int _simTimer;
	int _simDelay = 20;
	int _curSimStep;
private:
	sf::Vector2f _position = sf::Vector2f(-1, -1);
	sf::Vector2i _size;
	sf::RenderWindow* _window;
	std::vector<Cell> Cells;
	float _cellSize;
	bool _runningSimulation;
};

enum {
	checkingCells,
	applyingCells
};

