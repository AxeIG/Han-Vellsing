#include "Level.h"

//sf::View* Level::view = nullptr;
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) :BaseLevel()
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	GameObject::all_gameObjects.size();
	// initialise game objects
	view = window->getView();
	audio->addMusic("sfx/cantina.ogg", "cantina");
	audio->addMusic("sfx/Credits.ogg", "credits");
	world_map = map.getLevel();
	player.setInput(input);

	//collision boxes checkup

	

	wall1.setSize(sf::Vector2f(100, 100));
	wall1.setFillColor(sf::Color::Magenta);
	wall1.setPosition(1200, 550);
	wall1.setCollisionBox(0, 0, 100, 100);
	wall1.setCollider(true);

	player_box.setSize(sf::Vector2f(player.getCollisionBox().width, player.getCollisionBox().height));
	player_box.setFillColor(sf::Color::Red);

	//sword_box.setSize(sf::Vector2f(player.getSword().width, player.getSword().height));
	//sword_box.setFillColor(sf::Color::Blue);

	box_box.setSize(sf::Vector2f(wall1.getCollisionBox().width, wall1.getCollisionBox().height));
	box_box.setPosition(wall1.getCollisionBox().left, wall1.getCollisionBox().top);
	box_box.setFillColor(sf::Color::Green);

	

}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	player.handleInput(dt);
	if (input->isKeyDown(sf::Keyboard::Escape)) {
		gameState->setCurrentState(State::PAUSE_MENU);
		input->setKeyUp(sf::Keyboard::Escape);

	}
	else if (input->isKeyDown(sf::Keyboard::F)) {
		gameState->setCurrentState(State::BOSS_LEVEL);
	}
}

// Update game objects
void Level::update(float dt)
{

	for (int i = 0; i < GameObject::all_gameObjects.size() - 1; ++i) {
		//std::cout << GameObject::all_gameObjects[i] << std::endl;
	}

	//Collision Check for all GameObjects
	for(int i = 0; i < GameObject::all_gameObjects.size()-1; ++i)
	{

		if (!GameObject::all_gameObjects[i]->isCollider()) continue;

		for (int j = i + 1; j < GameObject::all_gameObjects.size(); ++j)
		{
			if (!GameObject::all_gameObjects[j]->isCollider()) continue;

			if (Collision::checkBoundingBox(GameObject::all_gameObjects[i], GameObject::all_gameObjects[j])) {

				//std::cout << "COLLIDED" << std::endl;
				/*GameObject::all_gameObjects[i]->collisionResponse(GameObject::all_gameObjects[j]);
				GameObject::all_gameObjects[j]->collisionResponse(GameObject::all_gameObjects[i]);*/
			}
		}
	}

	player_box.setPosition(player.getCollisionBox().left, player.getCollisionBox().top);
	//sword_box.setPosition(player.getSword().left, player.getSword().top);
	player.update(dt);

	//player.setPosition(window->getSize().x/2, window->getSize().y / 2);

	if (collision.checkBoundingBox(&player,&wall1)) {
		//std::cout << "WHOWHOWHOHWOHWOHWOHWOHOWHWO";
	}

	view.setCenter(player.getPosition().x, view.getCenter().y);
	window->setView(view);

}

// Render level
void Level::render()
{

	beginDraw();
	window->draw(wall1);
	window->draw(box_box);
	window->draw(player);
	window->draw(player_box); 
	//window->draw(sword_box);
	window->draw(player.player_sprite);
	
	map.render(window);
	endDraw();
}

