#pragma once
#include"Framework/TileMap.h"
#include"Player.h"
#include<map>

class Map :
	public TileMap
{
public:
	Map();

	int getMapLength() { return length; }
	sf::Vector2f getPosition() { return position; }
	int length;
};