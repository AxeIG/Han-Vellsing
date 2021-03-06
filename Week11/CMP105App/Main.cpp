// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include "Level.h"
#include "PauseMenu.h"
#include "MainMenu.h"
#include "ControlsMenu.h"
#include "CreditsMenu.h"
#include "LossMenu.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"


void windowProcess(sf::RenderWindow* window, Input* in)
{
	// Handle window events.
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
			break;
		case sf::Event::KeyPressed:
			// update input class
			in->setKeyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			//update input class
			in->setKeyUp(event.key.code);
			break;
		case sf::Event::MouseMoved:
			//update input class
			in->setMousePosition(event.mouseMove.x, event.mouseMove.y);
			BaseLevel::global_mouse_pos = window->mapPixelToCoords(in->getMouse(), window->getView());
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
				in->setLeftMouse(Input::MouseState::DOWN);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setRightMouse(Input::MouseState::DOWN);
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
				in->setLeftMouse(Input::MouseState::UP);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setRightMouse(Input::MouseState::UP);
			}
			break;
		default:
			// don't handle other events
			break;
		}
	}
}

int main()
{
	// Systems
	sf::RenderWindow window(sf::VideoMode(1200, 675), "CMP105_W11");
	AudioManager audioManager;
	Input input;
	GameState gameState, previous_gameState;

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;

	// Add Menues
	PauseMenu pause_menu(&window, &input, &gameState, &audioManager);
	MainMenu main_menu(&window, &input, &gameState, &audioManager);
	LossMenu loss_menu(&window, &input, &gameState, &audioManager);
	TutorialMenu tutorial_menu(&window, &input, &gameState, &audioManager);
	CreditsMenu credits_menu(&window, &input, &gameState, &audioManager);

	// Add Levels
	Level* level = new Level(&window, &input, &gameState, &audioManager);

	// Add Sounds
	audioManager.addMusic("sfx/Credits.ogg", "credits");
	audioManager.addMusic("sfx/LevelMusic.ogg", "levelMusic");
	audioManager.addMusic("sfx/mainMenu.wav", "mainMenu");
	audioManager.addSound("sfx/fireball.wav", "fireball");
	audioManager.addSound("sfx/flamethrower.wav", "flamethrower");
	audioManager.addSound("sfx/hit.wav", "hit");
	audioManager.addSound("sfx/sword.wav", "sword");
	audioManager.addSound("sfx/zombie.wav", "zombie");
	audioManager.addSound("sfx/shriek.ogg", "shriek");


	// Game Loop
	gameState.setCurrentState(State::MAIN_MENU);
	AudioManager::instance->playMusicbyName("mainMenu");
	previous_gameState = gameState;

	while (window.isOpen())
	{
		//Process window events
		windowProcess(&window, &input);

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();
		previous_gameState = gameState;
		switch (gameState.getCurrentState()) {

		case(State::MAIN_MENU):

			main_menu.handleInput(deltaTime);
			main_menu.update(deltaTime);
			main_menu.render();
			break;
		case(State::TUTORIAL_MENU):

			tutorial_menu.handleInput(deltaTime);
			tutorial_menu.update(deltaTime);
			tutorial_menu.render();
			break;
		case(State::LOSS_MENU):

			loss_menu.handleInput(deltaTime);
			loss_menu.update(deltaTime);
			loss_menu.render();
			break;
		case(State::LEVEL):
			// Call standard game loop functions (input, update and render)
			level->handleInput(deltaTime);
			level->update(deltaTime);
			level->render();
			break;

		case(State::PAUSE_MENU):

			pause_menu.handleInput(deltaTime);
			pause_menu.update(deltaTime);
			pause_menu.render();
			break;

		case(State::CREDITS_MENU):
			credits_menu.handleInput(deltaTime);
			credits_menu.update(deltaTime);
			credits_menu.render();
			break;
		default:
			break;
		}

		// Only check for transitions between different states
		if (previous_gameState.getCurrentState() != gameState.getCurrentState()) {
			if (gameState.getCurrentState() == State::LEVEL) {
				if (previous_gameState.getCurrentState() != State::PAUSE_MENU) {
					delete level;
					level = new Level(&window, &input, &gameState, &audioManager);
				}
			}

			if (gameState.getCurrentState() == State::LEVEL)
			{
				AudioManager::instance->stopAllMusic();
				AudioManager::instance->playMusicbyName("levelMusic");

			}
			if (gameState.getCurrentState() == State::CREDITS_MENU)
			{
				AudioManager::instance->stopAllMusic();
				AudioManager::instance->playMusicbyName("credits");

			}
			if (gameState.getCurrentState() == State::MAIN_MENU)
			{
				// Don't want to start music again when still in main menu/tutorial
				if (previous_gameState.getCurrentState() != State::TUTORIAL_MENU)
				{
					AudioManager::instance->stopAllMusic();;
					AudioManager::instance->playMusicbyName("mainMenu");

				}
			}
		}
		// Update input class, handle pressed keys
		// Must be done last.
		input.update();
	}

}