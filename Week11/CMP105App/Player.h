#pragma once
#include"Character.h"
#include<iostream>

class Player:
	public Character
{
public:
	enum class States{IDLE, WALK, JUMP, ATTACK, JUMP_ATTACK, ATTACK_RETURN};
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
	bool landed, falling, attacking;
	
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

	sf::Vector2f previous_position, jump_start_position;

};