#include "Cell.h"

Cell::Cell(sf::Vector2i gridPosition) {
	this->_gridPosition = gridPosition;
}

Cell::~Cell() {

}

bool Cell::isAlive() {
	return this->_alive;
}

void Cell::die() {
	this->_alive = false;
}

void Cell::born() {
	this->_alive = true;
}

sf::Vector2i Cell::gridPosition() {
	return this->_gridPosition;
}

void Cell::setScreenRect(sf::FloatRect screenRect) {
	this->_screenRect = screenRect;
}

sf::FloatRect Cell::getScreenRect() {
	return this->_screenRect;
}

void Cell::bornNeighbours() {

}

void Cell::revealGridPosition() {
	std::cout << "Cell[" << this->gridPosition().x << "][" << this->gridPosition().y << "]" << std::endl;
}