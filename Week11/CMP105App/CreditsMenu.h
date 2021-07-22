#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>

class CreditsMenu :
	public BaseLevel 
{
	public:
		CreditsMenu(sf::RenderWindow * hwnd, Input * in, GameState * gs, AudioManager * aud);
		~CreditsMenu();

		void handleInput(float dt) override;
		void update(float dt) override;
		void render() override;

	private:
		GameObject main_menu_button;
		sf::Texture main_menu_texture;

};

