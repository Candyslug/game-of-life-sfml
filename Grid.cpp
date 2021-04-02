#include "Grid.h"
#include "Cell.h"

Grid::Grid(sf::RenderWindow* window) {
	this->_window = window;
	std::string l;
	int data[1];
	std::ifstream myFile;
	myFile.open("autoload.cfg");
	for (int i = 0; i < 2; ++i)
	{
		myFile >> data[i];
	}
	myFile.close();
	this->_cellAmount = data[0];
	this->_simDelay = data[1];
	this->init();
	this->initCells();
	this->initCellNeighbours();
}

Grid::~Grid() {

}

void Grid::init() {
	this->_position = sf::Vector2f(0, 100);
	this->_size = sf::Vector2i(this->_window->getDefaultView().getSize().x, this->_window->getDefaultView().getSize().x);
}

void Grid::initCells() {
	Cells.clear();
	this->_cellSize = this->_window->getDefaultView().getSize().x / (float)this->_cellAmount;
	for (int x = 0; x < this->_cellAmount; x++) {
		for (int y = 0; y < this->_cellAmount; y++) {
			Cells.push_back(Cell(sf::Vector2i(x, y)));
		}
	}
	for (int i = 0; i < Cells.size(); i++) {
		Cells[i].ID = i;
		sf::FloatRect r;
		r.left = Cells[i].gridPosition().x * this->_cellSize + 1;
		r.top = (Cells[i].gridPosition().y * this->_cellSize) + this->_position.y + 1;
		r.width = this->_cellSize - 2;
		r.height = this->_cellSize - 2;
		Cells[i].setScreenRect(r);
	}
}

void Grid::initCellNeighbours() {
	for (int i = 0; i < Cells.size(); i++) {
		Cells[i].neighbours.clear();
		Cell TL(sf::Vector2i(Cells[i].gridPosition().x - 1, Cells[i].gridPosition().y - 1));
		Cell L(sf::Vector2i(Cells[i].gridPosition().x - 1, Cells[i].gridPosition().y));
		Cell BL(sf::Vector2i(Cells[i].gridPosition().x - 1, Cells[i].gridPosition().y + 1));
		Cell T(sf::Vector2i(Cells[i].gridPosition().x, Cells[i].gridPosition().y - 1));
		Cell B(sf::Vector2i(Cells[i].gridPosition().x, Cells[i].gridPosition().y + 1));
		Cell TR(sf::Vector2i(Cells[i].gridPosition().x + 1, Cells[i].gridPosition().y - 1));
		Cell R(sf::Vector2i(Cells[i].gridPosition().x + 1, Cells[i].gridPosition().y));
		Cell BR(sf::Vector2i(Cells[i].gridPosition().x + 1, Cells[i].gridPosition().y + 1));
		if (TL.gridPosition().x >= 0 && TL.gridPosition().y >= 0
			&& TL.gridPosition().x < this->_cellAmount && TL.gridPosition().y < this->_cellAmount) Cells[i].neighbours.push_back(TL);
		if (L.gridPosition().x >= 0 && L.gridPosition().y >= 0
			&& L.gridPosition().x < this->_cellAmount && L.gridPosition().y < this->_cellAmount) Cells[i].neighbours.push_back(L);
		if (BL.gridPosition().x >= 0 && BL.gridPosition().y >= 0
			&& BL.gridPosition().x < this->_cellAmount && BL.gridPosition().y < this->_cellAmount) Cells[i].neighbours.push_back(BL);
		if (T.gridPosition().x >= 0 && T.gridPosition().y >= 0
			&& T.gridPosition().x < this->_cellAmount && T.gridPosition().y < this->_cellAmount) Cells[i].neighbours.push_back(T);
		if (B.gridPosition().x >= 0 && B.gridPosition().y >= 0
			&& B.gridPosition().x < this->_cellAmount && B.gridPosition().y < this->_cellAmount) Cells[i].neighbours.push_back(B);
		if (TR.gridPosition().x >= 0 && TR.gridPosition().y >= 0
			&& TR.gridPosition().x < this->_cellAmount && TR.gridPosition().y < this->_cellAmount) Cells[i].neighbours.push_back(TR);
		if (R.gridPosition().x >= 0 && R.gridPosition().y >= 0
			&& R.gridPosition().x < this->_cellAmount && R.gridPosition().y < this->_cellAmount) Cells[i].neighbours.push_back(R);
		if (BR.gridPosition().x >= 0 && BR.gridPosition().y >= 0
			&& BR.gridPosition().x < this->_cellAmount && BR.gridPosition().y < this->_cellAmount) Cells[i].neighbours.push_back(BR);
	}
}

Cell Grid::getCell(sf::Vector2i gridPosition) {
	return Cells.at((size_t)(gridPosition.y + gridPosition.x * this->_cellAmount));
}

void Grid::runSimulation() {
	this->_runningSimulation = true;
}

void Grid::stopSimulation() {
	this->_runningSimulation = false;
	this->_simTimer = 0;
}

void Grid::pauseSimulation() {
	this->_runningSimulation = false;
}

void Grid::render() {
	this->drawMenu();
	this->drawCells();
	this->drawGrid();
}

void Grid::drawCells() {
	sf::Color clr = sf::Color(50, 50, 50, 255);
	sf::RectangleShape cellShape(sf::Vector2f(this->_cellSize, this->_cellSize));
	cellShape.setFillColor(clr);
	for (int i = 0; i < Cells.size(); i++) {
		cellShape.setPosition(Cells[i].gridPosition().x * this->_cellSize, (Cells[i].gridPosition().y * this->_cellSize) + this->_position.y);
		if (!Cells[i].isAlive()) {
			this->_window->draw(cellShape);
		}
	}
}

void Grid::drawGrid() {
	float lineThickness = 2.f;
	sf::Color clr = sf::Color(170, 170, 170, 255);
	sf::RectangleShape vLine(sf::Vector2f(lineThickness, this->_size.y));
	vLine.setFillColor(clr);
	sf::RectangleShape hLine(sf::Vector2f(this->_size.y, lineThickness));
	hLine.setFillColor(clr);
	for (int x = 0; x < this->_cellAmount; x++) {
		vLine.setPosition(sf::Vector2f(float(x * this->_cellSize) - float(lineThickness / 2.f), this->_position.y));
		this->_window->draw(vLine);
	}
	for (int y = 0; y < this->_cellAmount; y++) {
		hLine.setPosition(sf::Vector2f(this->_position.x, (y * this->_cellSize) - (lineThickness / 2.f) + this->_position.y));
		this->_window->draw(hLine);
	}
}

void Grid::drawMenu() {
	sf::RectangleShape statusShape;
	statusShape.setPosition(sf::Vector2f(10, 10));
	statusShape.setOutlineColor(sf::Color::Black);
	statusShape.setOutlineThickness(4);
	statusShape.setSize(sf::Vector2f(80, 80));
	sf::Color clr;
	if (this->_runningSimulation) {
		if (clr != sf::Color(sf::Color::Green)) {
			clr = sf::Color::Green;
		}
	}
	else if (!this->_runningSimulation) {
		if (clr != sf::Color(sf::Color::Red)) {
			clr = sf::Color::Red;
		}
	}
	statusShape.setFillColor(clr);
	this->_window->draw(statusShape);
	sf::RectangleShape barBG;
	barBG.setPosition(sf::Vector2f(110, 70));
	barBG.setOutlineColor(sf::Color::Black);
	barBG.setOutlineThickness(4);
	barBG.setSize(sf::Vector2f(this->_window->getSize().x - 130, 20));
	barBG.setFillColor(sf::Color(100, 100, 100, 255));
	this->_window->draw(barBG);
	float length = (this->_window->getSize().x - 130) - 110;
	float percen = (float)this->_simTimer / (float)this->_simDelay * 100.f;
	float f = (percen / 100.f) * length;
	sf::RectangleShape barShape;
	barShape.setPosition(sf::Vector2f(110, 70));
	barShape.setOutlineColor(sf::Color::Black);
	barShape.setOutlineThickness(4);
	barShape.setSize(sf::Vector2f(f, 20));
	barShape.setFillColor(sf::Color(0, 255, 0, 150));
	this->_window->draw(barShape);
}

void Grid::update() {
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*this->_window).x, sf::Mouse::getPosition(*this->_window).y);
	sf::FloatRect mouseRect(mousePos, sf::Vector2f(2, 2));
	if (this->_window->hasFocus()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			if (this->_runningSimulation) {
				this->stopSimulation();
			}
			else if (!this->_runningSimulation) {
				this->runSimulation();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
			this->stopSimulation();
			for (int i = 0; i < Cells.size(); i++) {
				Cells[i].die();
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			for (int i = 0; i < Cells.size(); i++) {
				if (mouseRect.intersects(Cells[i].getScreenRect())) {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						Cells[i].born();
						break;
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
						Cells[i].die();
						break;
					}
				}
			}
		}
	}
	this->updateCells();
}

void Grid::updateCells() {
	for (int i = 0; i < Cells.size(); i++) {
		Cells[i].aliveNeighbours = 0;
		for (int c = 0; c < Cells[i].neighbours.size(); c++) {
			if (Cells.at(getCell(sf::Vector2i(Cells[i].neighbours[c].gridPosition().x, Cells[i].neighbours[c].gridPosition().y)).ID).isAlive()) {
				Cells[i].aliveNeighbours += 1;
			}
		}
	}
	if (this->_runningSimulation) {
		this->_simTimer++;
		if (this->_curSimStep == checkingCells) {
			for (int i = 0; i < Cells.size(); i++) {
				Cells[i].aliveNeighbours = 0;
				for (int c = 0; c < Cells[i].neighbours.size(); c++) {
					if (Cells.at(getCell(sf::Vector2i(Cells[i].neighbours[c].gridPosition().x, Cells[i].neighbours[c].gridPosition().y)).ID).isAlive()) {
						Cells[i].aliveNeighbours += 1;
					}
				}
			}
			this->_curSimStep = applyingCells;
		}
		else if (this->_curSimStep == applyingCells) {
			if (this->_simTimer >= this->_simDelay) {
				for (int i = 0; i < Cells.size(); i++) {
					if (Cells[i].aliveNeighbours == 3) {
						Cells[i].born();
					}
					if (Cells[i].aliveNeighbours < 2) {
						Cells[i].die();
					}
					if (Cells[i].aliveNeighbours > 3) {
						Cells[i].die();
					}
				}
				this->_curSimStep = checkingCells;
				this->_simTimer = 0;
			}
		}
	}
}