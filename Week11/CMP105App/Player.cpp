#include"Player.h"
#include<iostream>

#define SWORD_WIDTH 100
#define ATTACK_ANIM_WIDTH 96
#define ANIM_HEIGHT 65
#define IDLE_WIDTH 38
#define JATTK_WIDTH 84
#define JUMP_WIDTH 61
#define WALK_WIDTH 66


Player::Player() : GameObject() {
	
	collision_layer = CollisionLayer::PLAYER;
	clock.restart();
	cooldown = clock.getElapsedTime();//Variable used for managing Skills and Jump Cooldown
	health = 100; //Variable representing the player's health
	landing = false;//Landing state
	attacking = false;

	//Setting the Player's collision box and characteristics
	setSize(sf::Vector2f(25, -40));
	setOrigin(getSize().x/2, 0.0f);
	setCollisionBox(0, 0, getSize().x, getSize().y);
	setCollider(true);
	//initialise physics variables
	velocity = sf::Vector2f(0, 0);
	step_velocity = sf::Vector2f(0, 0);
	scale = 100.0f;
	gravity = sf::Vector2f(0, 9.8) * scale;

	//Settling the sword's collision box
	//sword.setCollisionBox(getCollisionBox().left + getCollisionBox().width, getCollisionBox().top, SWORD_WIDTH, getSize().y);

	//Loading player spritesheet
	texture.loadFromFile("gfx/herospritesheet.png");
	player_sprite.setTexture(&texture);	
	

	initialiseAnimations();
	current_animation=& idle;
	AssignAnimation(idle, true);
	player_sprite.setTextureRect(current_animation->getCurrentFrame());

	

}

Player::~Player() {

}

void Player::setHealth(int health) {

	this->health = health;
}

int Player::getHealth() {

	return health;

}

void Player::handleInput(float dt) {//Handles Player Inputs by applying force to the character based on the pressed key

	//When The "W" key is pressed the player will start jumping
	if ((input->isKeyDown(sf::Keyboard::W)) && (!landing)) {
		Jump(dt);
		if (current_animation != &jump_attack) { AssignAnimation(jump, false); }
		//setSize(sf::Vector2f(135, 100));
	}

	//Once the character reaches it's max vertical velocity or the "W" key is removed it will enter a landing state
	else if (((!input->isKeyDown(sf::Keyboard::W)) && (velocity.y != 0)) || (velocity.y == -600)) {
		
	landing = true; 

	if (current_animation != &jump_attack) { AssignAnimation(jump, false); }
	}

	if (input->isKeyDown(sf::Keyboard::Enter)) {

		if (velocity.y != 0) {
			AssignAnimation(jump_attack, false);
		}
		else { 
			AssignAnimation(attack, false); 
		//setSize(sf::Vector2f(153, 75));
		}

	}

	//Managing vertical movement based on key input
	if (input->isKeyDown(sf::Keyboard::D)) {

		velocity.x= 250;
		if (velocity.y==0) {
			AssignAnimation(walk, true);
			//setSize(sf::Vector2f(87, 70));
		}

	}
	else if (input->isKeyDown(sf::Keyboard::A)) {

		velocity.x = -250;
		if (velocity.y == 0) { 
			AssignAnimation(walk, true);
			//setSize(sf::Vector2f(87, 70));
		}

	}
	else { //If the Player is in a statonary state it will switch to an Idle animation

		if ((velocity.y == 0)&&(current_animation!=&attack)) {

			AssignAnimation(idle, true);
			//setSize(sf::Vector2f(60, 70));
		}
		velocity.x = 0;
	}
}


void Player::update(float dt) {

	//Animates current animation
	current_animation->animate(dt);
	
	//Simulates gravity
	if (getPosition().y <= 600) {
		step_velocity += gravity * dt;
		setPosition(getPosition() + step_velocity * dt);
	}
	else if (landing) {

		AssignAnimation(idle, true);
		step_velocity.y = velocity.y = 0;
		landing = false;
	}

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



void Player::Jump(float dt) { //Simluates the character's jump

	if (velocity.y == 0) { velocity.y = -100; }
	//The longer the player presses "W", the higher the character goes
	if ((input->isKeyDown(sf::Keyboard::W)) && (velocity.y >= -600)) {

		--velocity.y;
	}
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


