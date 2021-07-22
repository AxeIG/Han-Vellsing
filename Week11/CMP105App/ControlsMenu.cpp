#include "ControlsMenu.h"

TutorialMenu::TutorialMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) :
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

	background_texture.loadFromFile("gfx/TutorialScreen.png");
	background.setTexture(&background_texture);
	
}

TutorialMenu::~TutorialMenu() {

}

void TutorialMenu::handleInput(float dt) {

	if (input->isLeftMouseDown()) {

		if (Collision::checkBoundingBox(&exit_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			gameState->setCurrentState(State::MAIN_MENU);
			input->setLeftMouse(Input::MouseState::UP);
		}
	}
	
}


void TutorialMenu::update(float dt) {

	sf::Vector2f viewSize = window->getView().getSize();
	sf::Vector2f viewCenter = window->getView().getCenter();


	//background.setSize(sf::Vector2f(static_cast<sf::Vector2f>(window->getSize())));
	background.setSize(viewSize);
	background.setPosition(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);

	//sf::Vector2f camera_center = window->getView().getCenter();
	exit_button.setPosition(viewCenter.x - exit_button.getSize().x / 2, viewCenter.y - exit_button.getSize().y / 2);

}


void TutorialMenu::render() {

	beginDraw();
	window->draw(background);
	window->draw(exit_button);
	endDraw();
}