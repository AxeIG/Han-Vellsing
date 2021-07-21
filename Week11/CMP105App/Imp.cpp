#include "Imp.h"

#define IMP_WIDTH 16
#define IMP_HEIGHT 32

Imp::Imp() {

	//initialise object variables
	//scale_factor = 5
	setPosition(0, 0);
	setSize(sf::Vector2f(IMP_WIDTH*scale_factor, IMP_HEIGHT*scale_factor));
	sprite.setSize(getSize());
	setCollisionBox(0, 0, getSize().x, getSize().y);
	setCollider(true);
	detection_radius = 300;

	// initialise physics variables
	velocity = sf::Vector2f(0, 0);


	//Loading player spritesheet
	texture.loadFromFile("gfx/ImpSpritesheet.png");
	sprite.setTexture(&texture);
	initialiseAnimations();
	handleAnimation();
	AssignAnimation(idle, true);
	sprite.setPosition(500, -250);


}

Imp::~Imp() {


}

void Imp::update(float dt) {

	current_animation->animate(dt);
	AssignAnimation(idle, true);

}
void Imp::collisionResponse(GameObject* gameobject) {
	sf::Vector2f gameobject_size = gameobject->getSize();
	sf::Vector2f gameobject_pos = gameobject->getPosition();

	if (gameobject->collision_layer == CollisionLayer::PLAYER) {
		if (getPosition().x < gameobject->getPosition().x) {

			velocity.x = 1;
		}
		else {
			velocity.x = -1;
		}
		if ((gameobject_pos.y + gameobject_size.y >= getPosition().y) && (gameobject_pos.x >= getPosition().x) && (gameobject_pos.x <= getPosition().x + getSize().x)) {

			//FireTornado attack
			state = ImpStates::TORNADO_ATTACK;
		}
		else if ((abs(getPosition().x - gameobject->getPosition().x) <= detection_radius)&&(getPosition().y==gameobject->getPosition().y)) {

			//generate FireBall
			state = ImpStates::ATTACK;
		}
	}
	if (gameobject->collision_layer == CollisionLayer::SWORD) {

		//GETHIT
	}

}

void Imp::handleAnimation() {

	if (state == ImpStates::ATTACK) {

		//AssignAnimation(attack, false);
	}
	else if (state == ImpStates::TORNADO_ATTACK) {
		//AssignAnimation(tornado_attack, false);
	}
	else {

		//AssignAnimation(idle, true);
	}
	
}

void Imp::initialiseAnimations() {

	idle.addFrame(sf::IntRect( 0,   1, 55, 67));
	idle.addFrame(sf::IntRect( 55,  1, 55, 67));
	idle.addFrame(sf::IntRect(110,  1, 55, 67));
	idle.addFrame(sf::IntRect(165,  1, 55, 67));
	idle.addFrame(sf::IntRect(  0, 68, 55, 67));
	idle.addFrame(sf::IntRect( 55, 68, 55, 67));
	idle.setFrameSpeed(1 / 10.f);
	



	current_animation = &idle;
	sf::IntRect frame_rectangle = current_animation->getCurrentFrame();
	sprite.setSize(sf::Vector2f(abs(frame_rectangle.width * scale_factor), abs(frame_rectangle.height * scale_factor)));


}


