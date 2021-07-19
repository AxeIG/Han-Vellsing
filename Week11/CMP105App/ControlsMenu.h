#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>


class ControlsMenu :
	public BaseLevel
{
public:

	ControlsMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~ControlsMenu();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render() override;

private:
	GameObject exit_button, background;
	sf::Texture exit_texture, background_texture;
};