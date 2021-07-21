#pragma once
#include"Character.h"
#include<iostream>

class Player:
	public Character
{
public:
	enum class PlayerStates{GROUNDED, JUMP, ATTACK, JUMP_ATTACK, ATTACK_RETURN, FALL};
	Player();
	Player(float x, float y);
	~Player();

	void handleInput(float dt);
	void update(float dt);

	sf::FloatRect getSword();
	bool getAttack();
	void checkAttack();

	void handleAnimation() override;

	void collisionResponse(GameObject* collider) override;
	void updateState() override;

	void initialisePlayer();

private:

	void initialiseAnimations() override;

	// State
	bool landed, falling, attacking, jump_attacking;
	
	//GameObject sword = GameObject();

	// Animation
	Animation idle, walk, attack, jump, jump_attack, attack_return, jump_attack_return;

	// Cooldowns
	sf::Clock clock;
	sf::Time cooldown;

	sf::Vector2f gravity, jump_hold_acceleration;
	const float speed = 5.f;

	// Physics simulations
	

public :

	PlayerStates state;
	sf::Vector2f previous_position, jump_start_position;

};