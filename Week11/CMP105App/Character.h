#pragma once
#include"Framework/GameObject.h"
#include"Framework/Animation.h"
class Character:
	public GameObject
{
public: 

	Character();
	~Character();


	virtual void update(float dt);
	virtual void handleAnimation();
	virtual void initialiseAnimations();

	void AssignAnimation(Animation& animation, bool looping);

	void setHealth(int health);
	int  getHealth();


	float scale_factor = 1.f;
	int health;
	GameObject sprite;
	sf::Texture texture;
	Animation* current_animation;

};

