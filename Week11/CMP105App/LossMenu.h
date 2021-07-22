#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>

class LossMenu :
	public BaseLevel
{
public:
	LossMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~LossMenu();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render() override;

private:
	GameObject main_menu_button, restart_button, you_died_text;
	sf::Texture main_menu_texture, restart_texture, you_died_text_texture;

};