#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud):
	BaseLevel()
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;


	//Initialise menu buttons
	exit_button.setPosition(sf::Vector2f(300, 200));
	exit_button.setSize(sf::Vector2f(200, 40));
	exit_button.setFillColor(sf::Color::Red);
	exit_button.setCollider(true);
	exit_button.setCollisionBox(0, 0, exit_button.getSize().x,exit_button.getSize().y);

	resume_button.setPosition(sf::Vector2f(300, 400));
	resume_button.setSize(sf::Vector2f(200, 40));
	resume_button.setFillColor(sf::Color::Black);
	resume_button.setCollider(true);
	resume_button.setCollisionBox(0, 0, resume_button.getSize().x, resume_button.getSize().y);
	


	
}

PauseMenu::~PauseMenu() {

}

void PauseMenu::handleInput(float dt) {

	if (input->isKeyDown(sf::Keyboard::Escape)) {
		gameState->setCurrentState(State::LEVEL);
		input->setKeyUp(sf::Keyboard::Escape);
	}

	if(input->isLeftMouseDown()) {

		if (Collision::checkBoundingBox(&exit_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			window->close();
		}
		if (Collision::checkBoundingBox(&resume_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			gameState->setCurrentState(State::LEVEL);
		}
	}
}


void PauseMenu::update(float dt) {
	

	resume_button.setPosition(window->getView().getCenter().x - resume_button.getSize().x / 2, resume_button.getPosition().y);
	exit_button.setPosition(window->getView().getCenter().x - exit_button.getSize().x / 2, exit_button.getPosition().y);
	

}


void PauseMenu::render() {

	window->draw(exit_button);
	window->draw(resume_button);
	endDraw();
}