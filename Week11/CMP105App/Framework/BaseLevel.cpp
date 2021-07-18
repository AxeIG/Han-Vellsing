#include "BaseLevel.h"

sf::Vector2f BaseLevel::global_mouse_pos = sf::Vector2f(0, 0);
BaseLevel::BaseLevel()
{
	window = nullptr;
	input = nullptr;
	gameState = nullptr;
	audio = nullptr;

	
}

BaseLevel::~BaseLevel()
{
}

// Begins rendering to the back buffer. Background colour set to light blue.
void BaseLevel::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void BaseLevel::endDraw()
{
	window->display();
}