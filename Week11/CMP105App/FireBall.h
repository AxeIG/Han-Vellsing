#pragma once
#include"Framework/GameObject.h"
#include"Framework/Animation.h"
#include"Framework/Collision.h"
class FireBall :
	public GameObject
{
public:
	FireBall();
	~FireBall();

	void update(float dt) override;
	void collisionResponse(GameObject* gameobject) override;
	void setStartPosition(sf::Vector2f start_position);
	sf::Vector2f getStartPosition();

	


	sf::Vector2f start_position;

	static const float fireball_speed;
	bool isOutOfRange();

		
	
 private:

	 float max_range = 500;
	Animation animation;

};

