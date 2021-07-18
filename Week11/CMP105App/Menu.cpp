#include "Menu.h"

Menu::Menu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud):
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

Menu::~Menu() {

}

void Menu::handleInput(float dt) {

	if (input->isKeyDown(sf::Keyboard::Escape)) {
		gameState->setCurrentState(State::LEVEL);
		input->setKeyUp(sf::Keyboard::Escape);
	}
}



void Menu::update(float dt) {
	
	if (input->isLeftMouseDown()) {

		if (Collision::checkBoundingBox(&exit_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
				window->close();
			std::cout << "EXIT " << std::endl;
		}
		if (Collision::checkBoundingBox(&resume_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			std::cout << "RESUME " << std::endl;
				gameState->setCurrentState(State::LEVEL);
		}
	}

	resume_button.setPosition(window->getView().getCenter().x - resume_button.getSize().x / 2, resume_button.getPosition().y);
	exit_button.setPosition(window->getView().getCenter().x - exit_button.getSize().x / 2, exit_button.getPosition().y);
	/*std::cout << "Position: " << exit_button.getPosition().x<<std::endl;
	sf::FloatRect collBox = exit_button.getCollisionBox();
	std::cout << "Coll Box: " << collBox.left << " " << collBox.width << std::endl;
	std::cout << "Mouse pos: " << input->getMouseX() << " " << input->getMouseY() << std::endl;
	std::cout << "Global Mouse pos: " << global_mouse_pos.x<< " " << global_mouse_pos.y << std::endl;*/

}


void Menu::render() {

	//beginDraw();
	window->draw(exit_button);
	window->draw(resume_button);
	endDraw();
}