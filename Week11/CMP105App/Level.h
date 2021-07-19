#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include <string>
#include <iostream>
#include "Framework/Collision.h"

#include"EntityManager.h"
#include"Player.h"
#include"Map.h"


class Level : public BaseLevel{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Level();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render();


private:
	// Default variables for level class.

	Player* player;
	sf::RectangleShape player_box/*, sword_box*/;
	sf::View view;
	GameObject wall1 = GameObject();
	GameObject ground_axis = GameObject();
	Collision collision;
	Map map;
	std::vector<GameObject>* world_map;

	 
};