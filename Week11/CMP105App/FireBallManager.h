#pragma once
#include "FireBall.h"
class FireBallManager 
{
public:
	FireBallManager();
	~FireBallManager();

	void spawn(float x, float y, float velocity);
	void update(float dt);
	void render(sf::RenderWindow* window);
	void checkCollisions(GameObject* gameobject);
	void deathCheck();
	std::vector<FireBall>* getFireBalls() { return &fireballs; }

private:

	std::vector<FireBall> fireballs;
	sf::Texture fireball_texture;
	FireBall fireball_template;

	const std::string fireball_file = "gfx/fire-ball.png";
};

