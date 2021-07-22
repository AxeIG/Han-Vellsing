#include "MainMenu.h"
#define POSITION_PER_BUTTON 1.f/4.f
MainMenu::MainMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud):
	BaseLevel()
{

	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	//Initialise menu buttons
	exit_button.setPosition(sf::Vector2f(0, 200));
	exit_button.setSize(sf::Vector2f(200, 60));
	//exit_button.setFillColor(sf::Color::Red);
	exit_button.setCollider(true);
	exit_button.setCollisionBox(0, 0, exit_button.getSize().x, exit_button.getSize().y);
	exit_texture.loadFromFile("gfx/ExitButton.png");
	exit_button.setTexture(&exit_texture);

	play_button.setPosition(sf::Vector2f(0, 400));
	play_button.setSize(sf::Vector2f(200, 60));
	//play_button.setFillColor(sf::Color::Red);
	play_button.setCollider(true);
	play_button.setCollisionBox(0, 0, exit_button.getSize().x, exit_button.getSize().y);
	play_texture.loadFromFile("gfx/PlayButton.png");
	play_button.setTexture(&play_texture);


	controls_button.setPosition(sf::Vector2f(0, 600));
	controls_button.setSize(sf::Vector2f(200, 60));
	//controls_button.setFillColor(sf::Color::Red);
	controls_button.setCollider(true);
	controls_button.setCollisionBox(0, 0, exit_button.getSize().x, exit_button.getSize().y);
	controls_texture.loadFromFile("gfx/TutorialButton.png");
	controls_button.setTexture(&controls_texture);

	background_texture.loadFromFile("gfx/MainMenu.png");
	background.setTexture(&background_texture);
	



}

MainMenu::~MainMenu() {

}

void MainMenu::handleInput(float dt) {

	
	if (input->isLeftMouseDown()) {

		if (Collision::checkBoundingBox(&exit_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			window->close();
			input->setLeftMouse(Input::MouseState::UP);
		}
		else if (Collision::checkBoundingBox(&play_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			gameState->setCurrentState(State::LEVEL);
			input->setLeftMouse(Input::MouseState::UP);
		}
		else if (Collision::checkBoundingBox(&controls_button, static_cast<sf::Vector2i>(global_mouse_pos))) {
			gameState->setCurrentState(State::TUTORIAL_MENU);
			input->setLeftMouse(Input::MouseState::UP);

		}
	}

}

void MainMenu::update(float dt) {

	sf::Vector2f viewSize = window->getView().getSize();
	sf::Vector2f viewCenter = window->getView().getCenter();

	int gap = POSITION_PER_BUTTON * viewSize.y;

	//background.setSize(sf::Vector2f(static_cast<sf::Vector2f>(window->getSize())));
	background.setSize(viewSize);
	background.setPosition(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);

	//sf::Vector2f camera_center = window->getView().getCenter();
	exit_button.setPosition(viewCenter.x - exit_button.getSize().x/2, viewCenter.y - exit_button.getSize().y/2 + gap * 1);
	play_button.setPosition(viewCenter.x - exit_button.getSize().x/2, viewCenter.y- play_button.getSize().y/2 - gap * 1);
	controls_button.setPosition(viewCenter.x - exit_button.getSize().x/2, viewCenter.y - controls_button.getSize().y/2 );
}


void MainMenu::render() {
	beginDraw();
	window->draw(background);
	window->draw(play_button);
	window->draw(controls_button);
	window->draw(exit_button);
	endDraw();

}

