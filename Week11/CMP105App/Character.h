#pragma once
#include"Framework/GameObject.h"
#include"Framework/Animation.h"
#include "Framework/Collision.h"
#include<vector>
class Character:
	public GameObject
{
public: 

	Character();
	~Character();


	virtual void update(float dt);
	virtual void handleAnimation();
	virtual void initialiseAnimations();
	virtual void updateState();
	void AssignAnimation(Animation& animation, bool looping);

	void setHealth(int health);
	int  getHealth();


	float scale_factor = 2.f;
	int health;
	GameObject sprite;
	sf::Texture texture;
	Animation* current_animation;

};

