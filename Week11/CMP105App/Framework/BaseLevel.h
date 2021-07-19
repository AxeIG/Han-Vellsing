#pragma once

#include <SFML/Graphics.hpp>
#include "Input.h"
#include "AudioManager.h"
#include "GameState.h"
#include <string>
#include <iostream>

enum class LevelName{NONE,LEVEL1, BOSS_LEVEL};
class BaseLevel
{
public:
	BaseLevel();
	~BaseLevel();

	virtual void handleInput(float dt) = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;

	LevelName level_name = LevelName::NONE;
	static sf::Vector2f global_mouse_pos;
protected:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager* audio;
};

