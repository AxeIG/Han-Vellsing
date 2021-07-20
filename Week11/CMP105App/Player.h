#pragma once
#include"Framework/GameObject.h"
#include"Framework/Animation.h"
#include<iostream>
class Player:
	public GameObject
{
public:

	Player();
	Player(float x, float y);
	~Player();

	void handleInput(float dt);
	void update(float dt);

	void Jump(float dt);
	void AssignAnimation(Animation &animation,bool looping);
	void handleAnimation();

	void setHealth(int health);
	int  getHealth();

	sf::FloatRect getSword();
	bool getAttack();
	void checkAttack();

	void collisionResponse(GameObject* collider) override;
	void OnStartOfFrame();

	void initialisePlayer();

private:

	void initialiseAnimations();

	// State
	int health;
	bool landed,falling, attacking;
	sf::Texture texture;
	//GameObject sword = GameObject();

	// Animation
	Animation idle, walk, attack, jump, jump_attack;
	Animation* current_animation;

	// Cooldowns
	sf::Clock clock;
	sf::Time cooldown;

	sf::Vector2f gravity, jump_hold_acceleration;
	const float speed = 5.f;

	// Physics simulations
	const float physics_scale = 25.f;

public :

	sf::Vector2f previous_position, jump_start_position;
	GameObject player_sprite = GameObject();




};