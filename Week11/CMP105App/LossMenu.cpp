#include "LossMenu.h"

LossMenu::LossMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) {

	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;


	you_died_text.setSize(sf::Vector2f(448, 40));
	you_died_text_texture.loadFromFile("gfx/you_died.png");
	you_died_text.setTexture(&you_died_text_texture);
		

	//Initialise menu buttons
	restart_button.setSize(sf::Vector2f(200, 40));
	restart_button.setFillColor(sf::Color::Green);
	restart_button.setCollider(true);
	restart_button.setCollisionBox(0, 0, restart_button.getSize().x, restart_button.getSize().y);

	main_menu_button.setSize(sf::Vector2f(200, 40));
	main_menu_button.setFillColor(sf::Color::Magenta);
	main_menu_button.setCollider(true);
	main_menu_button.setCollisionBox(0, 0, main_menu_button.getSize().x, main_menu_button.getSize().y);
}

LossMenu::~LossMenu() {

}

void LossMenu::handleInput(float dt) {

	if (input->isKeyDown(sf::Keyboard::Escape)) {
		gameState->setCurrentState(State::LEVEL);
		input->setKeyUp(sf::Keyboard::Escape);
	}

	
	if (input->isLeftMouseDown()) {
		if (Collision::checkBoundingBox(&main_menu_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			gameState->setCurrentState(State::MAIN_MENU);
			input->setLeftMouse(Input::MouseState::UP);
		}
		if (Collision::checkBoundingBox(&restart_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			gameState->setCurrentState(State::LEVEL);
		}
	}
	
}



void LossMenu::update(float dt) {

	sf::Vector2f viewSize = window->getView().getSize();
	sf::Vector2f viewCenter = window->getView().getCenter();


	//background.setSize(sf::Vector2f(static_cast<sf::Vector2f>(window->getSize())));
	

	//sf::Vector2f camera_center = window->getView().getCenter();
	main_menu_button.setPosition(viewCenter.x - main_menu_button.getSize().x / 2, viewCenter.y + main_menu_button.getSize().y);
	restart_button.setPosition(viewCenter.x - restart_button.getSize().x / 2, viewCenter.y - restart_button.getSize().y);
	you_died_text.setPosition(viewCenter.x - you_died_text.getSize().x / 2, viewCenter.y - viewSize.y / 2 + you_died_text.getSize().y);

}


void LossMenu::render() {

	//beginDraw();
	window->draw(you_died_text);
	window->draw(main_menu_button);
	window->draw(restart_button);
	endDraw();
}
