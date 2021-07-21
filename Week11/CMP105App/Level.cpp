#include "Level.h"

//sf::View* Level::view = nullptr;

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) :BaseLevel()
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	
	level_name = LevelName::LEVEL1;
	// initialise game objects
	background = new Background("gfx/MegaBigCloud.png", 0.03f, 2048, 704, 1024);
	background->setSize(sf::Vector2f(1200, 675));

	//background->setPosition(70, -352);
	


	/*layer1.setSize(sf::Vector2f(512, 352));
	layer1.setPosition(20, 0);
	layer1_texture.loadFromFile("gfx/clouds.png");
	layer1.setTexture(&layer1_texture);
	layer1.setTextureRect(sf::IntRect(0, 0, 256, 176));*/


	/*layer1_texture.loadFromFile("gfx/clouds.png");
	layer1.setTexture(&layer1_texture);
	layer1.setSize(sf::Vector2f(200, 200));
	layer1.setPosition(0, -200);
	layer1.setTextureRect(sf::IntRect(0, 0, 512, 176));*/

	layer2_texture.loadFromFile("gfx/town.png");
	layer2.setTexture(&layer2_texture);
	layer2.setSize(sf::Vector2f(1200, 675));
	layer2.setTextureRect(sf::IntRect(0,0,256,176));
	layer2.setPosition(0,-675);
	

	view = window->getView();
	audio->addMusic("sfx/cantina.ogg", "cantina");
	audio->addMusic("sfx/Credits.ogg", "credits");
	world_map = map.getLevel();


	player =new Player(128, -250);
	player->setInput(input);

	imp = new Imp();
	imp->setPosition(512 , -200);

	//collision boxes checkup
	player_box.setSize(sf::Vector2f(imp->getCollisionBox().width, imp->getCollisionBox().height));
	player_box.setFillColor(sf::Color::Red);

	//sword_box.setSize(sf::Vector2f(player.getSword().width, player.getSword().height));
	//sword_box.setFillColor(sf::Color::Blue);
}

Level::~Level()
{
	//Manually destroying pointers
	delete player;
	delete background;
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
	
	background->updateTextureCoordinates(dt);
	player->update(dt);
	imp->update(dt);
	//sword_box.setPosition(player.getSword().left, player.getSword().top);

	for (int i = 0; i < world_map->size(); i++){
		if ((*world_map)[i].isCollider()) {
			if (Collision::checkBoundingBox(player, &(*world_map)[i])) {

				player->collisionResponse(&(*world_map)[i]);
			}
		}
	}
	player_box.setPosition(imp->getCollisionBox().left, imp->getCollisionBox().top);


	if (player->getPosition().x <= view.getSize().x/2) {
		view.setCenter(view.getCenter().x, player->getPosition().y - 150);
	}
	else {
		view.setCenter(player->getPosition().x, player->getPosition().y - 150);
	}
	window->setView(view);
	background->setPosition(view.getCenter().x-view.getSize().x/2, view.getCenter().y-view.getSize().y/2);
	layer2.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y-layer2.getSize().y/2);
	
	if (Collision::checkBoundingBox(imp, player)) {

		imp->collisionResponse(player);
	}

	//std::cout << player->getPosition().x << " " << player->getPosition().y << std::endl;

}

// Render level
void Level::render()
{
	beginDraw();
	

	window->draw(*background);
	window->draw(layer2);
	map.render(window);
	window->draw(player_box); 
	window->draw((*player));
	window->draw((*imp));
	window->draw((imp->sprite));
	//window->draw(sword_box);
	window->draw(player->sprite);


	endDraw();
	player->updateState();
	

}

