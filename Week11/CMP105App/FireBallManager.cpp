#include "FireBallManager.h"


FireBallManager::FireBallManager() {
	
	//Initialise fireball
	fireball_texture.loadFromFile(fireball_file);
	fireball_template = FireBall();
	fireball_template.setTexture(&fireball_texture);
	fireball_template.setAlive(true);
	fireball_template.setVelocity(FireBall::fireball_speed, 0);
	fireball_template.setPosition(0, 0);

}

FireBallManager::~FireBallManager() {
	
	fireballs.clear();
}

void FireBallManager::spawn(float x, float y, float direction)
{
	fireball_template.setPosition(x, y - fireball_template.getSize().y/2); 
	fireball_template.setVelocity(FireBall::fireball_speed * -direction, 0);
	fireball_template.setStartPosition(fireball_template.getPosition());

	for (int i = 0; i < fireballs.size(); i++)
	{
		if (!fireballs[i].isAlive()) {
			fireballs[i].setPosition(x, y - fireballs[i].getSize().y/2);
			fireballs[i].setAlive(true);
			fireballs[i].setVelocity(FireBall::fireball_speed * -direction, 0);
			fireballs[i].setStartPosition(fireballs[i].getPosition());
			
			return;
		}
	}

	fireballs.push_back(fireball_template);

}

void FireBallManager::update(float dt)
{
	for (int i = 0; i < fireballs.size(); i++)
	{
		if (fireballs[i].isAlive()) {

			fireballs[i].update(dt);
		}
	}
	deathCheck();
}

void FireBallManager::deathCheck() {

	for (int i = 0; i < fireballs.size(); i++)
	{
		if (fireballs[i].isOutOfRange()) {
			fireballs[i].setAlive(false);
		}
	}

}


void FireBallManager::render(sf::RenderWindow* window)
{
	for (int i = 0; i < fireballs.size(); i++)
	{
		if (fireballs[i].isAlive()) {

			window->draw(fireballs[i]);
		}
	}

}

void FireBallManager::checkCollisions(GameObject* gameobject)
{
	for (int i = 0; i < fireballs.size(); i++)
	{
		if (fireballs[i].isAlive()) {

			if (Collision::checkBoundingBox(&fireballs[i], gameobject)) {
				fireballs[i].collisionResponse(gameobject);
			}
		}
	}

}


