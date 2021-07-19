#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>



class MainMenu :
	public BaseLevel
{
public:
	MainMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~MainMenu();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render() override;

private:
	GameObject exit_button, play_button, controls_button, background;
	sf::Texture exit_texture, play_texture, controls_texture, background_texture;

};