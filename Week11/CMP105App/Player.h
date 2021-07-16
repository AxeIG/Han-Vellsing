#pragma once
#include"Framework/GameObject.h"
#include"Framework/Animation.h"
#include<iostream>
class Player:
	public GameObject
{
public:

	Player();
	~Player();

	void handleInput(float dt);
	void update(float dt);

	void Jump(float dt);
	void AssignAnimation(Animation &animation,bool looping);

	void setHealth(int health);
	int  getHealth();

	sf::FloatRect getSword();
	bool getAttack();
	void checkAttack();

	void collisionResponse(GameObject* collider) override {

		std::cout << "uno" << std::endl;
	}


private:

	void initialiseAnimations();

	int health;
	float scale;
	bool landing, attacking;
	sf::Vector2f gravity, step_velocity;
	sf::Texture texture;
	//GameObject sword = GameObject();
	Animation idle, walk, attack, jump, jump_attack;
	Animation* current_animation;
	sf::Clock clock;
	sf::Time cooldown;

public :

GameObject player_sprite = GameObject();




};