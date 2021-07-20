#include"Player.h"
#include<iostream>

#define SWORD_WIDTH 100
#define ATTACK_ANIM_WIDTH 96
#define ANIM_HEIGHT 65
#define IDLE_WIDTH 38
#define JATTK_WIDTH 84
#define JUMP_WIDTH 61
#define WALK_WIDTH 66
#define PLAYER_HEIGHT 32
#define MAX_JUMP_HEIGHT 128

Player::Player() : GameObject() {
	
	setPosition(0, 0);
	initialisePlayer();
}

Player::Player(float x, float y) {

	initialisePlayer();
	setPosition(x, y);
	
}

void Player::initialisePlayer() {

	jump_start_position = getPosition();
	previous_position = getPosition();
	collision_layer = CollisionLayer::PLAYER;
	clock.restart();
	cooldown = clock.getElapsedTime();//Variable used for managing Skills and Jump Cooldown
	health = 100; //Variable representing the player's health
	landed = false;//Landing state
	falling = false;
	attacking = false;

	//Setting the Player's collision box and characteristics
	setSize(sf::Vector2f(20, 40));
	setOrigin(getSize().x / 2, getSize().y);
	setCollisionBox(0, 0, getSize().x, getSize().y);
	setCollider(true);
	//initialise physics variables
	velocity = sf::Vector2f(0, 0) * physics_scale;
	gravity = sf::Vector2f(0, 9.8) * physics_scale;

	//Settling the sword's collision box
	//sword.setCollisionBox(getCollisionBox().left + getCollisionBox().width, getCollisionBox().top, SWORD_WIDTH, getSize().y);

	//Loading player spritesheet
	texture.loadFromFile("gfx/herospritesheet.png");
	player_sprite.setTexture(&texture);


	initialiseAnimations();
	current_animation = &idle;
	AssignAnimation(idle, true);
	player_sprite.setTextureRect(current_animation->getCurrentFrame());
}

Player::~Player() {

}


#define MOVE_FORCE speed * physics_scale
#define JUMP_FORCE -speed * physics_scale
#define JUMP_FORCE_HOLD -9.8f * physics_scale // Cancel gravity

void Player::OnStartOfFrame() {

	//direction = sf::Vector2f(0.f, 0.f);

	if ((falling)&&(velocity.y == 0)) {

		falling = false;
		landed = true;
	}
	else if ((landed) && (velocity.y < 0)) {

		landed = false;
		falling = false;
	}
	else if ((landed) && (velocity.y > 0)) {
		
		std::cout << "Error! Landed Fall" << std::endl;
	}
	else if ((!falling) && (!landed) && (velocity.y >= 0)) {
		landed = false;
		falling = true;
	}
	else if ((landed) && (falling)) {

		std::cout << "Error! Landed and Falling" << std::endl;
	}

	velocity.x = 0;
	jump_hold_acceleration.y = 0;
	previous_position = getPosition();
}

void Player::handleInput(float dt) {//Handles Player Inputs by applying force to the character based on the pressed key

	//When The "W" key is pressed the player will start jumping
	if ((input->isKeyDown(sf::Keyboard::W)) && (!falling)) {

		if (landed) {
			velocity.y = JUMP_FORCE;
			jump_start_position = getPosition();
		}
		else if (abs(jump_start_position.y - getPosition().y) <= MAX_JUMP_HEIGHT) 
		{
			jump_hold_acceleration.y = JUMP_FORCE_HOLD;
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

	//Animates current animation
	current_animation->animate(dt);

	/*if (landing) {
		std::cout << "LANDING" << std::endl;
	}
	else { std::cout << "NOT" << std::endl; }*/

	//std::cout << velocity.y << " " << acceleration.y <<std::endl;

	sf::Vector2f offset = velocity*dt + 0.5f * (gravity + jump_hold_acceleration)*dt*dt;
	velocity += (gravity + jump_hold_acceleration)* dt;
	setPosition(getPosition() + offset);


	//Simulates gravity
	if (getPosition().y >= 0) {
		setPosition(getPosition().x, 0); 
		velocity.y = 0.0f;
		//acceleration.y = 0.0f;
	}
	if (getPosition().x < 0) {
		setPosition(0, getPosition().y);
		velocity.x = 0.0f;
		//acceleration.y = 0.0f;
	}
	//std::cout << "Offset.X" << offset.x << " " << "Offset.Y" << offset.y << std::endl;

	//Applies vertical and horizontal forces to the character
	if (velocity != sf::Vector2f(0, 0)) {
		move(velocity.x * dt, velocity.y * dt);
	}

	//Update sword CollisionBox coordonates
	/*if (!current_animation->getFlipped()) {
		sword.setCollisionBox(getCollisionBox().left + getCollisionBox().width, getCollisionBox().top, SWORD_WIDTH, getSize().y);
	}
	else sword.setCollisionBox(getCollisionBox().left - SWORD_WIDTH, getCollisionBox().top, SWORD_WIDTH, -getSize().y);*/

	//Depends on Animation being handled beforehand
	int new_x_position = getPosition().x-player_sprite.getSize().x/2 ;
	int new_y_position = getPosition().y - player_sprite.getSize().y;
	player_sprite.setPosition(new_x_position, new_y_position);
	player_sprite.setTextureRect(current_animation->getCurrentFrame());
}

void Player::collisionResponse(GameObject* gameobject) {

	//Dependend on player origin being at bottom mid
	if (gameobject->collision_layer == CollisionLayer::PLATFORM) {

		sf::Vector2f collider_pos = gameobject->getPosition();
		float  collider_size = gameobject->getCollisionBox().width;
		float  collider_right_point_Xpos = (collider_pos.x + collider_size);

		//Dependend on platform origin point being 0,0 (top_left corner)
		if (previous_position.y > collider_pos.y) {

			if ((previous_position.x >= collider_pos.x)&&(previous_position.x <= collider_right_point_Xpos)) {
				velocity.y = 0;
				setPosition(getPosition().x, collider_pos.y);
			}
		}
	}
}

void Player::Jump(float dt) { //Simluates the character's jump

	
}


void Player::AssignAnimation(Animation& animation, bool looping) {

	bool  is_flipped = current_animation->getFlipped();
	if (current_animation != &animation) {
		current_animation = &animation;
		current_animation->reset();
		current_animation->setLooping(looping);
		current_animation->setPlaying(true);

		sf::IntRect frame_rectangle = current_animation->getCurrentFrame();
		player_sprite.setSize(sf::Vector2f(abs(frame_rectangle.width), abs(frame_rectangle.height)));
	}

   //Flipping the character based on his non-zero horizontal velocity or else it keeps the previous flip state
	current_animation->setFlipped((velocity.x < 0 && velocity.x!=0) || (velocity.x==0 && is_flipped ));
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
	attack.addFrame(sf::IntRect(0, 0, ATTACK_ANIM_WIDTH, ANIM_HEIGHT));
	attack.addFrame(sf::IntRect(96, 0, ATTACK_ANIM_WIDTH, ANIM_HEIGHT));
	attack.addFrame(sf::IntRect(192, 0, ATTACK_ANIM_WIDTH, ANIM_HEIGHT));
	attack.addFrame(sf::IntRect(288, 0, ATTACK_ANIM_WIDTH, ANIM_HEIGHT));
	attack.addFrame(sf::IntRect(384, 0, ATTACK_ANIM_WIDTH, ANIM_HEIGHT));
	attack.addFrame(sf::IntRect(480, 0, ATTACK_ANIM_WIDTH, ANIM_HEIGHT));
	attack.setFrameSpeed(1.f / 10.f);

	//Jump attack frames
	jump_attack.addFrame(sf::IntRect(1536, 0, JATTK_WIDTH, ANIM_HEIGHT));
	jump_attack.addFrame(sf::IntRect(1632, 0, JATTK_WIDTH, ANIM_HEIGHT));
	jump_attack.addFrame(sf::IntRect(0, 65, JATTK_WIDTH, ANIM_HEIGHT));
	jump_attack.setFrameSpeed(1.f / 6.f);


}
void Player::setHealth(int health) {

	this->health = health;
}

int Player::getHealth() {

	return health;

}



