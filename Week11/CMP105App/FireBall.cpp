#include "FireBall.h"

const float FireBall::fireball_speed = 3;
FireBall::FireBall(){
	
	//set velocity;
	//initialiseAnimation
	//AssignAnimation
	collision_layer = CollisionLayer::PROJECTILE;
	animation.addFrame(sf::IntRect(0, 0, 19, 16));
	animation.addFrame(sf::IntRect(19, 0, 19, 16));
	animation.addFrame(sf::IntRect(38, 0, 19, 16));
	animation.setFrameSpeed(1 / 3.f);
	setSize(sf::Vector2f(50, 50));

	float thirth_width = getSize().x / 3;
	float thirth_height = getSize().y / 3;
	setCollisionBox(thirth_width, thirth_height, thirth_width, thirth_height);
}

FireBall::~FireBall()
{

}

void FireBall::update(float dt)
{
	animation.animate(dt);
	setTextureRect(animation.getCurrentFrame());
	move(getVelocity());
	if (getVelocity().x > 0) {
		animation.setFlipped(true);
	}
	else(animation.setFlipped(false));
}

void FireBall::collisionResponse(GameObject* gameobject)
{
	if (gameobject->collision_layer == CollisionLayer::PLAYER) {

		setAlive(false);
	}

}

void FireBall::setStartPosition(sf::Vector2f start_position)
{
	this->start_position = start_position;
}

sf::Vector2f FireBall::getStartPosition()
{
	return start_position;
}

bool FireBall::isOutOfRange() {

	if (abs(getPosition().x - getStartPosition().x) > max_range) {
		return true;
	}
	return false;
}
