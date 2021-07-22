#include"Player.h"
#include<iostream>

#define SWORD_WIDTH 30 * scale_factor
// Animation definitions
#define ATTACK_ANIM_WIDTH 96
#define ANIM_HEIGHT 65
#define IDLE_WIDTH 38
#define JATTK_WIDTH 84
#define JUMP_WIDTH 61
#define WALK_WIDTH 66

// Player data
#define PLAYER_HEIGHT 40
#define PLAYER_WIDTH 16
#define MAX_JUMP_HEIGHT 128

// Physics
#define MOVE_FORCE speed * physics_scale
#define JUMP_FORCE -speed * physics_scale
#define JUMP_FORCE_HOLD -9.8f * physics_scale


Player::Player() : Character() {
	
	setPosition(0, 0);
	initialisePlayer();
}

Player::Player(float x, float y) {

	initialisePlayer();
	setPosition(x, y);
}

void Player::initialisePlayer() {

	// cooldown = clock.getElapsedTime();//Variable used for managing Skills and Jump Cooldown
	// clock.restart();

	jump_start_position = getPosition();
	previous_position = getPosition();
	collision_layer = CollisionLayer::PLAYER;
	health = 100; //Variable representing the player's health
	landed = false;//Landing state
	falling = false;
	attacking = false;
	jump_attacking = false;

	// Setting the Player's collision box and characteristics
	setSize(sf::Vector2f(PLAYER_WIDTH * scale_factor, PLAYER_HEIGHT * scale_factor));
	sprite.setSize(getSize());
	setCollisionBox(0, 0, getSize().x, getSize().y);
	setCollider(true);

	// initialise physics variables
	velocity = sf::Vector2f(0, 0) * physics_scale;
	gravity = sf::Vector2f(0, 9.8) * physics_scale;

	//Loading player spritesheet
	texture.loadFromFile("gfx/herospritesheet.png");
	sprite.setTexture(&texture);
	initialiseAnimations();
	handleAnimation();

	// Settling the sword's collision box and characteristics
	sword.setCollider(false);
	sword.collision_layer = CollisionLayer::SWORD;
	sword.setSize(sf::Vector2f(SWORD_WIDTH + getSize().x , getSize().y));
	sword.setCollisionBox(0, 0, sword.getSize().x, sword.getSize().y);
}

Player::~Player() {

}

void Player::updateState() {

	//direction = sf::Vector2f(0.f, 0.f);
	//std::cout << velocity.x << " " << velocity.y << std::endl;
	if ((state == PlayerStates::GROUNDED)) {
		//std::cout << "I AM UPDATING" << std::endl;
		if (velocity.y > 0) {
			std::cout << "FALL" << std::endl;
			state = PlayerStates::FALL;
		}
		else if (velocity.y < 0) {
			std::cout << "JUMP" << std::endl;

			state = PlayerStates::JUMP;
		}
		else if (attacking) {
			std::cout << "ATTACK" << std::endl;

			state = PlayerStates::ATTACK;
		}
	}
	
	else if (state == PlayerStates::ATTACK) {
		if (!current_animation->getPlaying()) {
			attacking = false;
			sword.setCollider(true);
			state = PlayerStates::ATTACK_RETURN;
		}
	}
	else if (state == PlayerStates::ATTACK_RETURN) 
	{
		sword.setCollider(false);
		// TODO: make the animation breakable
		if (!current_animation->getPlaying()) {
			if (velocity.y == 0) {
				state = PlayerStates::GROUNDED;
			}
			else if (velocity.y > 0) {
				state = PlayerStates::FALL;
			}
			else if (velocity.y < 0) {
				state = PlayerStates::JUMP;
			}
		}
	}
	else if (state == PlayerStates::JUMP) {
	
		if (attacking) {
			state = PlayerStates::JUMP_ATTACK;
			sword.setCollider(true);
		}
		else if (velocity.y >= 0) {
			state = PlayerStates::FALL;
		}
	}
	else if (state == PlayerStates::FALL) {
	    if (attacking) {
			state = PlayerStates::JUMP_ATTACK;
			sword.setCollider(true);
		}
		else if (velocity.y == 0) {
			state = PlayerStates::GROUNDED;
		}
	}
	else if (state == PlayerStates::JUMP_ATTACK) {

		sword.setCollider(false);
		attacking = false;
		if (velocity.y == 0) {
			state = PlayerStates::GROUNDED;

		}
	}

	velocity.x = 0;
	jump_hold_acceleration.y = 0;

	previous_position = getPosition();
	
}

void Player::handleInput(float dt) {//Handles Player Inputs by applying force to the character based on the pressed key


	if (input->isKeyDown(sf::Keyboard::Enter)) {

			attacking = true;
		/*else { 
			jump_attacking = true; 
			if (current_animation != &jump_attack) {
				
			}
		}
	*/
	}
	//When The "W" key is pressed the player will start jumping

	if (input->isKeyDown(sf::Keyboard::W)){// && (!falling)&&(!attacking)) {

		if (state == PlayerStates::GROUNDED) {
			velocity.y = JUMP_FORCE;
			jump_start_position = getPosition();
		}
		else if (abs(jump_start_position.y - getPosition().y) <= MAX_JUMP_HEIGHT) 
		{
			if (state == PlayerStates::JUMP) {
				
				jump_hold_acceleration.y = JUMP_FORCE_HOLD;
			}
		}
		
	}

	//Managing vertical movement based on key input
	if (input->isKeyDown(sf::Keyboard::D)) {

		velocity.x += MOVE_FORCE;

	}
	if (input->isKeyDown(sf::Keyboard::A)) {

		velocity.x -= MOVE_FORCE;
	}


}

void Player::update(float dt) {

	// After handling input

	// Update movement
	sf::Vector2f offset_pos = velocity*dt + 0.5f * (gravity + jump_hold_acceleration)*dt*dt;
	velocity += (gravity + jump_hold_acceleration)* dt;
	// setPosition(getPosition() + offset_pos);
	
	if (velocity != sf::Vector2f(0, 0)) { 
		// Applies vertical and horizontal forces to the character
		move(velocity.x * dt, velocity.y * dt);
	}

	//Update sword (if it is active)

	if (sword.isCollider()) {
		if (current_animation->getFlipped()) {
			sword.setPosition(getPosition().x - sword.getSize().x + getSize().x, getPosition().y);
		}
		else {
			sword.setPosition(getPosition().x, getPosition().y);
		}

	}
	// Update sprite and animations
	current_animation->animate(dt);
	handleAnimation();
}

void Player::collisionResponse(GameObject* gameobject) {

	sf::Vector2f collider_pos = gameobject->getPosition();
	sf::Vector2f  collider_size = sf::Vector2f(gameobject->getCollisionBox().width, gameobject->getCollisionBox().height);
	float  collider_right_point_Xpos = (collider_pos.x + collider_size.x);
	float bottom_middle = previous_position.x + getSize().x / 2;

	//Platform collsiion
	if (gameobject->collision_layer == CollisionLayer::PLATFORM) {
		
		//check if on top
		//Dependend on platform origin point being 0,0 (top_left corner)
		if (previous_position.y + getSize().y <= collider_pos.y) {

			if ((bottom_middle >= collider_pos.x) && (bottom_middle <= collider_right_point_Xpos)) {
				velocity.y = 0;
				setPosition(getPosition().x, collider_pos.y - getSize().y);
				//std::cout << getPosition().y << " " << previous_position.y << std::endl;
				
			}
		}
	}
	//Wall collision
	else if (gameobject->collision_layer == CollisionLayer::WALL) {
		
		//Check player top
		if(previous_position.y >= collider_pos.y+collider_size.y) {
			if ((previous_position.x + getSize().x > collider_pos.x) && (previous_position.x < collider_right_point_Xpos)) {
					velocity.y = 0;
					setPosition(getPosition().x, collider_pos.y+collider_size.y);
			}
		}
		//check player bottom
		else if (previous_position.y + getSize().y <= collider_pos.y) {
			if ((previous_position.x + getSize().x > collider_pos.x) && (previous_position.x < collider_right_point_Xpos)) {
				velocity.y = 0;
				setPosition(getPosition().x, collider_pos.y - getSize().y);
				//	std::cout << getPosition().y << " " << previous_position.y << std::endl;
			}
		}
		//Check from left
		else if ((previous_position.x + getSize().x >= collider_pos.x) && (velocity.x > 0)) {
			velocity.x = 0;
			setPosition(collider_pos.x - getSize().x, getPosition().y);

		}
		//Check from right
		else if ((previous_position.x <= collider_pos.x + collider_size.x) && (velocity.x < 0)) {
			velocity.x= 0;
			setPosition(collider_pos.x+collider_size.x , getPosition().y);
		}
		
	}

	else if (gameobject->collision_layer == CollisionLayer::FIRE) {

		health-=0.25;
		std::cout << health << " ";
		
	}
	else if (gameobject->collision_layer == CollisionLayer::PROJECTILE) {

		health -= 5;
		std::cout << health << " ";
	}
		

}


void Player::handleAnimation() {

	if (state == PlayerStates::JUMP_ATTACK) {

		AssignAnimation(jump_attack, false);
	}
	else if (state == PlayerStates::JUMP) {
		AssignAnimation(jump, false);
	}
	else if (state == PlayerStates::FALL) {
		AssignAnimation(jump, false);
	}
	else if (state == PlayerStates::ATTACK) {

		AssignAnimation(attack, false);
	}
	else if (state == PlayerStates::ATTACK_RETURN) {
		AssignAnimation(attack_return, false);
	}
	else if (state==PlayerStates::GROUNDED) {

		if (velocity.x != 0) {
			AssignAnimation(walk, true);
		}
		else {
			AssignAnimation(idle, true);
		}
	}
	/*if (jump_attacking && !landed) {

		if (current_animation != &jump_attack) {
		
		}
		AssignAnimation(jump_attack, false);

	}
	else if (jump_attacking) {

		jump_attacking = false;
	}
	else if (attacking) {

		if (!current_animation->getPlaying()) {
			attacking = false;
		}
		AssignAnimation(attack, false);
	}
	else if ((landed) && (velocity.x != 0)) {

		std::cout << "I SHOULD WALK" << std::endl;
		AssignAnimation(walk, true);
	}
	else if ((!landed) && (current_animation != &jump_attack)) {
		AssignAnimation(jump, false);
	}
	else{
		AssignAnimation(idle, true);
	}*/

}

void Player::initialiseAnimations() {

	//Idle Animation Frames
	idle.addFrame(sf::IntRect(864, 0, IDLE_WIDTH, ANIM_HEIGHT));
	idle.addFrame(sf::IntRect(960, 0, IDLE_WIDTH, ANIM_HEIGHT));
	idle.addFrame(sf::IntRect(1056, 0, IDLE_WIDTH, ANIM_HEIGHT));
	idle.addFrame(sf::IntRect(1152, 0, IDLE_WIDTH, ANIM_HEIGHT));
	idle.setFrameSpeed(1.f / 4.f);

	//Walk animation Frames
	walk.addFrame(sf::IntRect(576, 65, WALK_WIDTH, ANIM_HEIGHT));
	walk.addFrame(sf::IntRect(672, 65, WALK_WIDTH, ANIM_HEIGHT));
	walk.addFrame(sf::IntRect(768, 65, WALK_WIDTH, ANIM_HEIGHT));
	walk.addFrame(sf::IntRect(864, 65, WALK_WIDTH, ANIM_HEIGHT));
	walk.addFrame(sf::IntRect(960, 65, WALK_WIDTH, ANIM_HEIGHT));
	walk.addFrame(sf::IntRect(1056, 65, WALK_WIDTH, ANIM_HEIGHT));
	walk.addFrame(sf::IntRect(1152, 65, WALK_WIDTH, ANIM_HEIGHT));
	walk.addFrame(sf::IntRect(1248, 65, WALK_WIDTH, ANIM_HEIGHT));
	walk.addFrame(sf::IntRect(1344, 65, WALK_WIDTH, ANIM_HEIGHT));
	walk.addFrame(sf::IntRect(1440, 65, WALK_WIDTH, ANIM_HEIGHT));
	walk.addFrame(sf::IntRect(1536, 65, WALK_WIDTH, ANIM_HEIGHT));
	walk.addFrame(sf::IntRect(1632, 65, WALK_WIDTH, ANIM_HEIGHT));
	walk.setFrameSpeed(1.f / 10.f);

	//Jump animation Frames
	jump.addFrame(sf::IntRect(96, 65, JUMP_WIDTH, ANIM_HEIGHT));
	jump.addFrame(sf::IntRect(192, 65, JUMP_WIDTH, ANIM_HEIGHT));
	jump.addFrame(sf::IntRect(288, 65, JUMP_WIDTH, ANIM_HEIGHT));
	jump.addFrame(sf::IntRect(384, 65, JUMP_WIDTH, ANIM_HEIGHT));
	jump.addFrame(sf::IntRect(480, 65, JUMP_WIDTH, ANIM_HEIGHT));
	jump.setFrameSpeed(1.f / 11.f);

	//Attack frames
	//attack.addFrame(sf::IntRect(0, 0, ATTACK_ANIM_WIDTH, ANIM_HEIGHT));
	attack.addFrame(sf::IntRect(96, 0, ATTACK_ANIM_WIDTH, ANIM_HEIGHT));
	attack.addFrame(sf::IntRect(192, 0, ATTACK_ANIM_WIDTH, ANIM_HEIGHT));
	attack.setFrameSpeed(1.f / 10.f);
	
	attack_return.addFrame(sf::IntRect(288, 0, ATTACK_ANIM_WIDTH, ANIM_HEIGHT));
	attack_return.addFrame(sf::IntRect(384, 0, ATTACK_ANIM_WIDTH, ANIM_HEIGHT));
	attack_return.addFrame(sf::IntRect(480, 0, ATTACK_ANIM_WIDTH, ANIM_HEIGHT));
	attack_return.setFrameSpeed(1.f / 10.f);




	//Jump attack frames
	jump_attack.addFrame(sf::IntRect(1632, 0, JATTK_WIDTH, ANIM_HEIGHT));
	jump_attack.addFrame(sf::IntRect(0, 65, JATTK_WIDTH, ANIM_HEIGHT));
	jump_attack.addFrame(sf::IntRect(384, 65, JUMP_WIDTH, ANIM_HEIGHT));
	jump_attack.addFrame(sf::IntRect(480, 65, JUMP_WIDTH, ANIM_HEIGHT));
	jump_attack.setFrameSpeed(1.f / 8.f);

	current_animation = &idle;
	sf::IntRect frame_rectangle = current_animation->getCurrentFrame();
	sprite.setSize(sf::Vector2f(abs(frame_rectangle.width * scale_factor), abs(frame_rectangle.height * scale_factor)));
}

sf::FloatRect Player::getSword() {
	//return sword.getCollisionBox();
	return sf::FloatRect();
}

void Player::checkAttack() {

	//if current_animation.getFrame()==frame 1 && frame 2 attacking==true else attacking==false
	
}

bool Player::getAttack() {

	return attacking;
}





