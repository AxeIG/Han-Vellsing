#include "Imp.h"

#define IMP_WIDTH 16
#define IMP_HEIGHT 32
#define TORNADO_SIZE 160 * scale_factor

Imp::Imp() {

	collision_layer = CollisionLayer::NONE;
	sprite.collision_layer = CollisionLayer::NONE;
	//initialise object variables
	can_attack = false;
	can_tornado = false;

	detection_radius = 128 * scale_factor;

	setSize(sf::Vector2f(IMP_WIDTH*scale_factor, IMP_HEIGHT*scale_factor));
	sprite.setSize(getSize());
	setCollisionBox(-detection_radius,-(TORNADO_SIZE+getSize().y) ,detection_radius*2+getSize().x, TORNADO_SIZE + getSize().y*2);
	setCollider(true); 
	

	// initialise physics variables
	velocity = sf::Vector2f(-1, 0);
	setVelocity(velocity);


	
	initialiseAnimations();
	handleAnimation();
	AssignAnimation(idle, true);
	state = ImpStates::IDLE;


}

Imp::~Imp() {


}

void Imp::update(float dt) {

	//std::cout <<"UPDATE" << std::endl;
	updateState();
	current_animation->animate(dt);
	handleAnimation();


}

void Imp::updateState() {

	if (state == ImpStates::TORNADO_ATTACK) {

		//std::cout << "TORNADO" << std::endl;
		if (!current_animation->getPlaying()) {

			//setDamageColliderON
			state = ImpStates::TORNADO_RETURN;
			

		}
	}
	else if (state == ImpStates::TORNADO_RETURN) {
		//std::cout << "TORNADO_RETURN" << std::endl;
		if (!current_animation->getPlaying()) {
			//setDamageColliderOFF
			can_tornado = false;
			state = ImpStates::IDLE;
		}
	}
	else if (state == ImpStates::IDLE) {

		//std::cout << "IDLE" << std::endl;
		if (can_tornado) {
		//	std::cout << "WHY DON'T I TORNADO" << std::endl;
			state = ImpStates::TORNADO_ATTACK;
		}
		else if (can_attack) {
			state = ImpStates::ATTACK;
		}
		

	}
	else if (state == ImpStates::ATTACK) {

		if (can_tornado) {
			state = ImpStates::TORNADO_ATTACK;
		}
		if (!current_animation->getPlaying()) {
			state = ImpStates::IDLE;
			can_attack = false;
		}
	}

}

bool Imp::shouldSpawnFireball()
{
	return (state == ImpStates::ATTACK && !current_animation->getPlaying());
}

void Imp::collisionResponse(GameObject* gameobject) {

	sf::Vector2f gameobject_size = gameobject->getSize();
	sf::Vector2f gameobject_pos = gameobject->getPosition();
	float  gameobject_mid = gameobject_pos.x + gameobject_size.x / 2;
	float imp_sprite_right = sprite.getPosition().x + sprite.getSize().x;
	float imp_sprite_left = sprite.getPosition().x;
	float imp_sprite_bottom = sprite.getPosition().y+sprite.getSize().y;
	float imp_sprite_top = sprite.getPosition().y;
	float gameobject_top = gameobject_pos.y;
	float gameobject_bottom = gameobject_pos.y + gameobject_size.y;

	
	if (gameobject->collision_layer == CollisionLayer::PLAYER) {
		if (getPosition().x < gameobject_pos.x) {

			velocity.x = -1;
		}
		else {

			velocity.x = 1;
		}
		//if player's bottom extend is higher than the imp's sprite top extend
		if (gameobject_bottom <= imp_sprite_top) {

			//
			if((gameobject_mid>= imp_sprite_left) && (gameobject_mid<= imp_sprite_right)) {

			//FireTornado attack
				can_tornado = true;
			}
		}
		else {

		
			can_attack = true;
		}
		
	}
	if (gameobject->collision_layer == CollisionLayer::SWORD) {
	
		if (Collision::checkBoundingBox(gameobject, &sprite)) {
			
			setAlive(false);
		}
	}
}

void Imp::handleAnimation() {

	//std::cout << this << std::endl;
	 if (state == ImpStates::TORNADO_ATTACK) {

		sprite.collision_layer = CollisionLayer::FIRE;
		AssignAnimation(tornado_attack, false);
	 }
	 else if (state == ImpStates::TORNADO_RETURN) {
		 sprite.collision_layer = CollisionLayer::NONE;
		 AssignAnimation(tornado_return, false);
	 }
	else if (state == ImpStates::ATTACK) {
		 AssignAnimation(attack, false);
	}
	else if(state==ImpStates::IDLE){
		 AssignAnimation(idle, true);
	}
	
}

void Imp::initialiseAnimations() {

	idle.addFrame(sf::IntRect( 0,   1, 55, 67));
	idle.addFrame(sf::IntRect( 55,  1, 55, 67));
	idle.addFrame(sf::IntRect(110,  1, 55, 67));
	idle.addFrame(sf::IntRect(165,  1, 55, 67));
	idle.addFrame(sf::IntRect(  0, 68, 55, 67));
	idle.addFrame(sf::IntRect( 55, 68, 55, 67));
	idle.setFrameSpeed(1/10.f);

	attack.addFrame(sf::IntRect(110,  68, 64, 64));
	attack.addFrame(sf::IntRect(  0, 135, 64, 64));
	attack.addFrame(sf::IntRect( 64, 135, 64, 64));
	attack.addFrame(sf::IntRect(128, 135, 64, 64));
	attack.setFrameSpeed(1/6.f);


	tornado_attack.addFrame(sf::IntRect(0, 198 + 100, 74, 160 - 100)); // no tornado cut top 100 pixels of sprite
	tornado_attack.addFrame(sf::IntRect(74, 198 + 100, 74, 160 - 100 )); // no tornado cut top 100 pixels of sprite
	tornado_attack.addFrame(sf::IntRect(148, 198 + 100, 74, 160 - 100)); // no tornado cut top 100 pixels of sprite
	tornado_attack.addFrame(sf::IntRect(0, 358 + 100, 74, 160 - 100)); // no tornado cut top 100 pixels of sprite
	tornado_attack.addFrame(sf::IntRect(74, 358, 74, 160));
	tornado_attack.addFrame(sf::IntRect(148, 358, 74, 160));
	tornado_attack.setFrameSpeed(1 / 8.f);


	tornado_attack.addFrame(sf::IntRect(0, 358 + 100, 74, 160 - 100));
	tornado_return.addFrame(sf::IntRect(148, 198 + 100, 74, 160 - 100));
	tornado_return.addFrame(sf::IntRect(74, 198 + 100, 74, 160 - 100));
	tornado_return.setFrameSpeed(1 / 8.f);



	current_animation = &idle;
	sf::IntRect frame_rectangle = current_animation->getCurrentFrame();
	sprite.setSize(sf::Vector2f(abs(frame_rectangle.width * scale_factor), abs(frame_rectangle.height * scale_factor)));


}


