#include "Level.h"

//sf::View* Level::view = nullptr;
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) :BaseLevel()
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	player =new Player(100, -100);

	GameObject::all_gameObjects.size();
	level_name = LevelName::LEVEL1;
	// initialise game objects
	view = window->getView();
	audio->addMusic("sfx/cantina.ogg", "cantina");
	audio->addMusic("sfx/Credits.ogg", "credits");
	world_map = map.getLevel();
	player->setInput(input);

	//collision boxes checkup

	wall1.setSize(sf::Vector2f(2, 1000));
	wall1.setOrigin(1, 500);
	wall1.setPosition(0, 0);
	wall1.setCollisionBox(0, 0, 0, 0);
	wall1.setCollider(false);
	wall1.setFillColor(sf::Color::Yellow);

	player_box.setSize(sf::Vector2f(player->getCollisionBox().width, player->getCollisionBox().height));
	player_box.setFillColor(sf::Color::Red);

	//sword_box.setSize(sf::Vector2f(player.getSword().width, player.getSword().height));
	//sword_box.setFillColor(sf::Color::Blue);

	ground_axis.setSize(sf::Vector2f(1200, 2));
	ground_axis.setOrigin(600,1);
	ground_axis.setPosition(0,0);
	ground_axis.setCollisionBox(0, 0, 0, 0);
	ground_axis.setFillColor(sf::Color::Yellow);
	ground_axis.setCollider(false);

	

}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	player->handleInput(dt);
	if (input->isKeyDown(sf::Keyboard::Escape)) {
		gameState->setCurrentState(State::PAUSE_MENU);
		input->setKeyUp(sf::Keyboard::Escape);

	}
	else if (input->isKeyDown(sf::Keyboard::F)) {
		gameState->setCurrentState(State::BOSS_LEVEL);
	}
	if (input->isKeyDown(sf::Keyboard::F)) {

		gameState->setCurrentState(State::MAIN_MENU);
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


	player_box.setPosition(player->getCollisionBox().left, player->getCollisionBox().top);
	//sword_box.setPosition(player.getSword().left, player.getSword().top);

	player->update(dt);

	//player.setPosition(window->getSize().x/2, window->getSize().y / 2);

	if (collision.checkBoundingBox(player,&wall1)) {
		//std::cout << "WHOWHOWHOHWOHWOHWOHWOHOWHWO";
	}

	view.setCenter(player->getPosition().x, player->getPosition().y);
	window->setView(view);


}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(wall1);
	window->draw(ground_axis);
	window->draw((*player));
	window->draw(player_box); 
	//window->draw(sword_box);
	window->draw(player->player_sprite);
	map.render(window);
	endDraw();
	player->OnStartOfFrame();
	

}

