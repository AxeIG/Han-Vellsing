#include "ControlsMenu.h"

ControlsMenu::ControlsMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) :
	BaseLevel()
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;


	//Initialise menu buttons
	exit_button.setPosition(sf::Vector2f(300, 200));
	exit_button.setSize(sf::Vector2f(200, 40));
	//exit_button.setFillColor(sf::Color::Red);
	exit_button.setCollider(true);
	exit_button.setCollisionBox(0, 0, exit_button.getSize().x, exit_button.getSize().y);
	exit_texture.loadFromFile("gfx/ExitButton.png");
	exit_button.setTexture(&exit_texture);

	background_texture.loadFromFile("gfx/ControlsBackground.png");
	background.setTexture(&background_texture);

}

ControlsMenu::~ControlsMenu() {

}

void ControlsMenu::handleInput(float dt) {

	if (input->isLeftMouseDown()) {

		if (Collision::checkBoundingBox(&exit_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			gameState->setCurrentState(State::MAIN_MENU);
		}
	}
	
}


void ControlsMenu::update(float dt) {

	background.setSize(sf::Vector2f(static_cast<sf::Vector2f>(window->getSize())));
}


void ControlsMenu::render() {

	beginDraw();
	window->draw(background);
	window->draw(exit_button);
	endDraw();
}