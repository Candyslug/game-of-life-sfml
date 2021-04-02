#include "Window.h"
#include "Grid.h"
#include "Label.h"
#include <fstream>

Window::Window(std::string title, sf::Vector2i dimensions) {
	this->_title = title;
	this->_dimensions = dimensions;
	this->initRenderWindow();
}

Window::~Window() {
}

void Window::initRenderWindow() {
	this->_window = new sf::RenderWindow(sf::VideoMode(
		this->_dimensions.x,
		this->_dimensions.y),
		this->_title,
		sf::Style::Titlebar | sf::Style::Close);
	this->_window->setFramerateLimit(60);
	this->_window->setVerticalSyncEnabled(false);
}

void Window::close() {
	this->_window->close();
}

void Window::update() {
	Grid myGrid(this->_window);
	Label gridSizeLabel("External\\asset\\font\\sans.ttf", 20, sf::Vector2f(380, 5));
	Label simTimerLabel("External\\asset\\font\\sans.ttf", 20, sf::Vector2f(380, 32));
	Label keybindLabel("External\\asset\\font\\sans.ttf", 20, sf::Vector2f(680, 5));
	keybindLabel.setString("Up/Down Arrow Key: Cell Count");
	Label simSpeedLabel("External\\asset\\font\\sans.ttf", 20, sf::Vector2f(680, 32));
	simSpeedLabel.setString("Left/Right Arrow Key: Sim Speed");
	Label enterLabel("External\\asset\\font\\sans.ttf", 20, sf::Vector2f(100, 5));
	enterLabel.setString("Enter: Start/Stop");
	Label backspaceLabel("External\\asset\\font\\sans.ttf", 20, sf::Vector2f(100, 32));
	backspaceLabel.setString("Backspace: Reset");
	//================================================//
	while (this->_window->isOpen()) {
		sf::Event event;
		while (this->_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				this->_window->close();
			if (event.type == sf::Event::KeyReleased && this->_window->hasFocus())
			{
				if (event.key.code == sf::Keyboard::Up) {
					myGrid._cellAmount += 1;
					myGrid.init();
					myGrid.initCells();
					myGrid.initCellNeighbours();
					myGrid.stopSimulation();
				}
				if (event.key.code == sf::Keyboard::Down) {
					myGrid._cellAmount -= 1;
					myGrid.init();
					myGrid.initCells();
					myGrid.initCellNeighbours();
					myGrid.stopSimulation();
				}
				if (event.key.code == sf::Keyboard::Left) {
					if (myGrid._simDelay > 1)
						myGrid._simDelay -= 1;
				}
				if (event.key.code == sf::Keyboard::Right) {
					myGrid._simDelay += 1;
				}
			}
		}
		myGrid.update();
		//================================================//
		this->_window->clear(sf::Color::White);
		myGrid.render();
		//================================================//
		char gridSize[64];
		sprintf_s(gridSize, "Grid Size: [%i][%i]", myGrid._cellAmount, myGrid._cellAmount);
		gridSizeLabel.setString(gridSize);
		gridSizeLabel.render(this->_window);
		char timerC[64];
		float percen = (float)myGrid._simTimer / (float)myGrid._simDelay * 100.f;
		sprintf_s(timerC, "Frame: %i/%i (%1.0f percent)", myGrid._simTimer, myGrid._simDelay, percen);
		simTimerLabel.setString(timerC);
		simTimerLabel.render(this->_window);
		keybindLabel.render(this->_window);
		simSpeedLabel.render(this->_window);
		backspaceLabel.render(this->_window);
		enterLabel.render(this->_window);
		//================================================//
		this->_window->display();
	}

}