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
#include"Background.h"
#include"ImpManager.h"
#include"Player.h"
#include"Map.h"
#include"Imp.h"


class Level : public BaseLevel{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Level();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render();

	
private:
	// Default variables for level class.
	sf::View view;

	Map map;
	std::vector<GameObject>* world_map_assets;

	Player* player;
	Background* background;
	GameObject village_bg;
	ImpManager imp_manager;
	sf::Texture village_bg_texture, background_texture;
	GameObject player_health_bar;
	GameObject player_health_bar_border;

	// used for debug purposes
	//GameObject wall1 = GameObject();
	//GameObject ground_axis = GameObject();
	//sf::RectangleShape sword_box;
};