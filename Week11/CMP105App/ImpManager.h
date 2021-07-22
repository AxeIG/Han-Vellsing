#pragma once
#include "Imp.h"
#include "FireBallManager.h"

class ImpManager{



public:

	ImpManager();
	~ImpManager();

	void spawn(int x, int y);
	void update(float dt);
	void render(sf::RenderWindow* window);
	void checkCollisions(GameObject* gameobject);
	std::vector<Imp>* getImps() { return &imps; }
	FireBallManager* getFireballManager(){ return &fireball_manager; }

	bool areAllImpsDead();

private:

	FireBallManager fireball_manager;
	std::vector<Imp> imps;
	sf::Texture imp_texture;
	Imp imp_template;
	const std::string imp_file = "gfx/ImpSpritesheet.png";

};