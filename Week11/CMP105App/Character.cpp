#include "Character.h"

Character::Character() {


}

Character::~Character() {


}

void Character::update(float dt) {

}

void Character::handleAnimation() {


}

void Character::AssignAnimation(Animation& animation, bool looping) {
	bool  is_flipped = current_animation->getFlipped();
	if (current_animation != &animation) {
		current_animation = &animation;
		current_animation->reset();
		current_animation->setLooping(looping);
		current_animation->setPlaying(true);

		sf::IntRect frame_rectangle = current_animation->getCurrentFrame();
		//sprite.setPosition(getPosition().x, getPosition().y);
		sprite.setSize(sf::Vector2f(abs(frame_rectangle.width*scale_factor), abs(frame_rectangle.height*scale_factor)));
	}
	//Flipping the character based on his non-zero horizontal velocity or else it keeps the previous flip state
	current_animation->setFlipped((velocity.x < 0 && velocity.x != 0) || (velocity.x == 0 && is_flipped));

	// Depends on Animation being handled beforehand
	// Keeps sprite centered to the center of the player
	int new_x_position = getPosition().x - sprite.getSize().x / 2 + getSize().x / 2;
	int new_y_position = getPosition().y - sprite.getSize().y + getSize().y;
	sprite.setPosition(new_x_position, new_y_position);
	sprite.setTextureRect(current_animation->getCurrentFrame());

}

void Character::initialiseAnimations() {


}

void Character::setHealth(int helath) {

	this->health = health;
}


int  Character::getHealth() {

	return health;
}
