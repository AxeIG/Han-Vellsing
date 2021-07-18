#include "Menu.h"

Menu::Menu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;


	//Initialise menu buttons
	exit_button.setPosition(sf::Vector2f(0, 0));
	exit_button.setSize(sf::Vector2f(200, 40));
	exit_button.setFillColor(sf::Color::Red);
	exit_button.setCollider(true);
	exit_button.setCollisionBox(0, 0, exit_button.getSize().x,exit_button.getSize().y);

	resume_button.setPosition(sf::Vector2f(300, 500));
	resume_button.setSize(sf::Vector2f(200, 40));
	resume_button.setFillColor(sf::Color::Black);
	resume_button.setCollider(true);
	resume_button.setCollisionBox(0, 0, resume_button.getSize().x, resume_button.getSize().y);

}

Menu::~Menu() {

}

void Menu::handleInput(float dt) {

	if (input->isKeyDown(sf::Keyboard::Escape)) {
		gameState->setCurrentState(State::LEVEL);
		input->setKeyUp(sf::Keyboard::Escape);
	}
}

void Menu::update(float dt) {
	
	
	if (Collision::checkBoundingBox(&exit_button, sf::Vector2i(input->getMouseX(), input->getMouseY()))) {
		if (input->isLeftMouseDown()) {

			window->close();
		}
	}
	if ((Collision::checkBoundingBox(&resume_button, sf::Vector2i(input->getMouseX(), input->getMouseY())))&&(input->isLeftMouseDown())) {
			gameState->setCurrentState(State::LEVEL);
		}
	}


void Menu::render() {

	beginDraw();
	window->draw(exit_button);
	window->draw(resume_button);
	endDraw();
}