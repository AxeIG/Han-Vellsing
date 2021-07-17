#include"Map.h"

#include <iostream>

Map::Map() {

	texture.loadFromFile("gfx/tiles.png");

	//SETUP values for tiles, textures and collison

	//Initialise air tile (0)

	GameObject tile = GameObject();
	tile.setSize(sf::Vector2f(48, 32));
	tile.setCollisionBox(0, 0, 48, 32);
	tile.setCollider(false);
	tile.setTextureRect(sf::IntRect(91, 64, 48, 32));
	tileSet.push_back(tile);


	//Initialise brick ground tile (1)
	tile = GameObject(CollisionLayer::GROUND);
	tile.setSize(sf::Vector2f(48, 32));
	tile.setCollisionBox(0, 0, 48, 32);
	tile.setTextureRect(sf::IntRect(32, 64, 48, 32));
	tile.setCollider(true);
	tileSet.push_back(tile);

	//Initialise stone ground tile (2)
	tile = GameObject(CollisionLayer::GROUND);
	tile.setSize(sf::Vector2f(48, 32));
	tile.setCollisionBox(0, 0, 48, 32);
	tile.setCollider(true);
	tile.setTextureRect(sf::IntRect(384, 128, 48, 32));
	tileSet.push_back(tile);


	mapDimensions = sf::Vector2u(11, 5);

	tileMap = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0,
			  0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0,
			  2, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0
	};

	setPosition(sf::Vector2f(0, 300));
	buildLevel();
}
