#include "ImpManager.h"

ImpManager::ImpManager()
{

	imp_texture.loadFromFile(imp_file);
	imp_template = Imp();
	imp_template.setAlive(true);
	imp_template.sprite.setTexture(&imp_texture);
}

ImpManager::~ImpManager()
{
	imps.clear();
}

void ImpManager::spawn(int x, int y)
{
	imp_template.setPosition(x, y);
	//replaces the first dead imp with a new one
	for (int i = 0; i < imps.size(); i++)
	{
		if (!imps[i].isAlive()) {
		
			imps[i].setPosition(x, y);
			imps[i].setAlive(true);;
			return;
		}
		
	}
	//if no dead imp was found
	imps.push_back(imp_template);

}

void ImpManager::update(float dt)
{
	for (int i = 0; i < imps.size(); i++)
	{

		if (imps[i].isAlive()) {
			imps[i].update(dt);
			if (imps[i].shouldSpawnFireball()) {
				std::cout << "FIRE AT `IM" << std::endl;
			}
		}
	}
}

void ImpManager::render(sf::RenderWindow* window)
{

	for (int i = 0; i < imps.size(); i++)
	{
		if (imps[i].isAlive()) {
			window->draw(imps[i].sprite);
		}
	}

}


void ImpManager::checkCollisions(GameObject* gameobject)
{
	for (int i = 0; i < imps.size(); i++)
	{
		if (imps[i].isAlive()) {
		
			if (Collision::checkBoundingBox(&imps[i], gameobject)) {
				imps[i].collisionResponse(gameobject);
			}
		}

	}
}


