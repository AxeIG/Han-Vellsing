#pragma once
#include"SFML/Graphics.hpp"
#include"Framework/GameObject.h"

class Background:
	public GameObject
{
public:

	Background();
	Background(const char* file_name, float time_per_pixel, int width, int height, int display_width);
	~Background();

	void updateTextureCoordinates(float dt);

private:
	
	float time_per_pixel;
	float time_passed;
	int width, height;
	int display_width, display_start_index;
	sf::Texture texture;
};

