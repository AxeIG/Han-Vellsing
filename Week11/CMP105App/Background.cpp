#include "Background.h"

Background::Background(){

}

Background::Background(const char* file_name, float time_per_pixel, int width, int height, int display_width) {

	
	texture.loadFromFile(file_name);
	setTexture(&texture);
	display_start_index = 0;
	this->time_per_pixel = time_per_pixel;
	this->width = width;
	this->height = height;
	this->display_width = display_width;
	setTextureRect(sf::IntRect(0, 0, this->width, this->height));
	time_passed = 0.f;
}

Background::~Background() {

}


void Background::updateTextureCoordinates(float dt) {

	time_passed += dt;
	if (time_passed >= time_per_pixel) {
		time_passed = 0;

		// Move a pixel
		++display_start_index;

		if (display_start_index >= display_width) {

			display_start_index -= display_width;
		}

		setTextureRect(sf::IntRect(display_start_index, 0, display_width, height));

	}



}
