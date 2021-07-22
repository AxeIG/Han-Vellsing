#include "FireBallManager.h"

#define FIREBALL_SPEED 50.f
FireBallManager::FireBallManager() {



	fireball_texture.loadFromFile(fireball_file);
	fireball_template = FireBall();
	fireball_template.setTexture(&fireball_texture);
	fireball_template.setAlive(true);
	fireball_template.setVelocity(FIREBALL_SPEED, 0);

}

FireBallManager::~FireBallManager() {

	fireballs.clear();
}

void FireBallManager::spawn(float x, float y, float direction)
{
	fireball_template.setPosition(x, y);
	fireball_template.setVelocity(FIREBALL_SPEED * direction, 0);
	fireball_template.setStartPosition (sf::Vector2f(x, y));
	for (int i = 0; i < fireballs.size(); i++)
	{
		if (!fireballs[i].isAlive()) {
			fireballs[i].setPosition(x, y);
			fireballs[i].setAlive(true);
			fireballs[i].setVelocity(FIREBALL_SPEED * direction, 0);
			fireballs[i].setStartPosition(sf::Vector2f(x, y));
			
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


