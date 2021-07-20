#include"Map.h"

#define TILE_SIZE 32
#define CUT_SIZE 16
Map::Map() {

	texture.loadFromFile("gfx/tiles.png");

	//SETUP values for tiles, textures and collison

	//Initialise air tile (0)
	
	GameObject tile = GameObject();
	tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	tile.setCollisionBox(0, 0, TILE_SIZE, TILE_SIZE);
	tile.setCollider(false);
	tile.setTextureRect(sf::IntRect(CUT_SIZE, CUT_SIZE, CUT_SIZE, CUT_SIZE));
	tileSet.push_back(tile);
		

	//Initialise long stone platform tile tile (1-5)
	for (int i = 0; i < 5; i++)
	{
		tile.collision_layer = CollisionLayer::PLATFORM;
		tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
		tile.setCollisionBox(0, 0, TILE_SIZE, TILE_SIZE);
		tile.setCollider(true);
		tile.setTextureRect(sf::IntRect(32+i* CUT_SIZE, CUT_SIZE, CUT_SIZE, CUT_SIZE));
		tileSet.push_back(tile);

	}

	
	//Initialise brick ground tile (6-11)
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++) {
			tile = GameObject(CollisionLayer::GROUND);
			tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			tile.setCollisionBox(0, 0, TILE_SIZE, TILE_SIZE);
			tile.setCollider(false);
			tile.setTextureRect(sf::IntRect(32 + j * CUT_SIZE, 64 + i * CUT_SIZE, CUT_SIZE, CUT_SIZE));
			tileSet.push_back(tile);
		}
	}

	//Initialise sand ground tiles(12-17)
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++) {
			tile = GameObject(CollisionLayer::GROUND);
			tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			tile.setCollisionBox(0, 0, TILE_SIZE, TILE_SIZE);
			tile.setCollider(false);
			tile.setTextureRect(sf::IntRect(384 + j * CUT_SIZE, 128 + i * CUT_SIZE, CUT_SIZE, CUT_SIZE));
			tileSet.push_back(tile);
		}
	}

	//Initialise wall tiles(18-23)
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++) {
			tile = GameObject(CollisionLayer::WALL);
			tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			tile.setCollisionBox(0, 0, TILE_SIZE, TILE_SIZE);
			tile.setCollider(true);
			tile.setTextureRect(sf::IntRect(224 + j * CUT_SIZE, 112 + i * CUT_SIZE, 16, 16));
			tileSet.push_back(tile);
		}
	}



	mapDimensions = sf::Vector2u(11, 5);

	tileMap = { 0, 0, 0, 0, 0,12, 13, 14, 0, 0, 0,
			  0, 0, 0, 0, 0, 15, 16, 17, 0, 0, 0,
			  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			  0, 0, 1, 2, 3, 4, 5, 0, 0, 18, 19,
			  0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 21,
			  0, 0 ,0 ,0 ,0, 0, 0, 0, 0, 22, 23
	};

	
	for (size_t i = 0; i < mapDimensions.y; i++)
	{
		for (int j = 0; j < mapDimensions.x; j++);
		//collum=j+11
		//line=i*11+j


	}

	setPosition(sf::Vector2f(0, -static_cast<float>((mapDimensions.y+1) * TILE_SIZE)));
	buildLevel();
}
