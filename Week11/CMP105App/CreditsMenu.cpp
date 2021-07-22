#include "CreditsMenu.h"

CreditsMenu::CreditsMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) {

	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	main_menu_button.setPosition(sf::Vector2f(300, 400));
	main_menu_button.setSize(sf::Vector2f(200, 40));
	main_menu_button.setFillColor(sf::Color::Magenta);
	main_menu_button.setCollider(true);
	main_menu_button.setCollisionBox(0, 0, main_menu_button.getSize().x, main_menu_button.getSize().y);
	main_menu_texture.loadFromFile("gfx/MainMenuButton.png");
	main_menu_button.setTexture(&main_menu_texture);

	you_won_text.setSize(sf::Vector2f(448, 40));
	you_won_texture.loadFromFile("gfx/you_won.png");
	you_won_text.setTexture(&you_won_texture);

}

CreditsMenu::~CreditsMenu() {

}

void CreditsMenu::handleInput(float dt) {

	if (input->isKeyDown(sf::Keyboard::Escape)) {
		gameState->setCurrentState(State::LEVEL);
		input->setKeyUp(sf::Keyboard::Escape);
	}


	if (input->isLeftMouseDown()) {
		if (Collision::checkBoundingBox(&main_menu_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			gameState->setCurrentState(State::MAIN_MENU);
			input->setLeftMouse(Input::MouseState::UP);
		}
	}

}



void CreditsMenu::update(float dt) {

	sf::Vector2f viewSize = window->getView().getSize();
	sf::Vector2f viewCenter = window->getView().getCenter();


	sf::Vector2f camera_center = window->getView().getCenter();
	main_menu_button.setPosition(camera_center.x - main_menu_button.getSize().x / 2, camera_center.y - main_menu_button.getSize().y);

	you_won_text.setPosition(viewCenter.x - you_won_text.getSize().x / 2, viewCenter.y - viewSize.y / 2 + you_won_text.getSize().y);
}


void CreditsMenu::render() {

	window->draw(you_won_text);
	window->draw(main_menu_button);
	endDraw();
}
