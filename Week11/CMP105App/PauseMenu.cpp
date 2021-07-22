#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud):
	BaseLevel()
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	
	//Initialise menu buttons
	main_menu_button.setPosition(sf::Vector2f(300, 200));
	main_menu_button.setSize(sf::Vector2f(200, 40));
	main_menu_button.setFillColor(sf::Color::Red);
	main_menu_button.setCollider(true);
	main_menu_button.setCollisionBox(0, 0, main_menu_button.getSize().x,main_menu_button.getSize().y);

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

		if (Collision::checkBoundingBox(&main_menu_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			gameState->setCurrentState(State::MAIN_MENU);
			input->setLeftMouse(Input::MouseState::UP);
		}
		if (Collision::checkBoundingBox(&resume_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			gameState->setCurrentState(State::LEVEL);
			input->setLeftMouse(Input::MouseState::UP);
		}
	}
}



void PauseMenu::update(float dt) {
	
	sf::Vector2f camera_center = window->getView().getCenter();

	
	resume_button.setPosition(camera_center.x - main_menu_button.getSize().x / 2, camera_center.y - main_menu_button.getSize().y);

	
	main_menu_button.setSize(sf::Vector2f(200, 40));
	main_menu_button.setPosition(camera_center.x - resume_button.getSize().x / 2, camera_center.y + resume_button.getSize().y);

}


void PauseMenu::render() {

	window->draw(main_menu_button);
	window->draw(resume_button);
	endDraw();
}