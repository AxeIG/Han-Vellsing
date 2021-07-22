#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) :BaseLevel()
{
	level_name = LevelName::LEVEL1;
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;
	view = window->getView();

	// initialise game objects
	imp_manager.spawn(512, -110);
	imp_manager.spawn(1150, -300);
	imp_manager.spawn(1300, -400);

	background = new Background("gfx/MegaBigCloud.png", 0.03f, 2048, 704, 1024);
	background->setSize(sf::Vector2f(1200, 675));

	village_bg_texture.loadFromFile("gfx/town.png");
	village_bg.setTexture(&village_bg_texture);
	village_bg.setSize(sf::Vector2f(1200, 675));
	village_bg.setTextureRect(sf::IntRect(0,0,256,176));
	village_bg.setPosition(0,-675);

	world_map_assets = map.getLevel();

	player = new Player(128, -250);
	player->setAlive(true);
	player->setInput(input);

	sword_box.setSize(sf::Vector2f(player->sword.getSize()));
	sword_box.setFillColor(sf::Color::Blue);
}

Level::~Level()
{
	delete player;
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
		gameState->setCurrentState(State::CREDITS_MENU);
	}
}

// Update game objects
void Level::update(float dt)
{
	if (!player->isAlive()) {
		gameState->setCurrentState(State::LOSS_MENU);
		return;
	}
	bool all_enemies_dead = false;
	all_enemies_dead = all_enemies_dead || imp_manager.areAllImpsDead();


	if (all_enemies_dead) {
		gameState->setCurrentState(State::CREDITS_MENU);
		return;
	}

	// Update the characters
	player->update(dt);
	imp_manager.update(dt);

	// COLLISION HANDLING
	// Collisions:: Player <-> map
	for (int i = 0; i < world_map_assets->size(); i++){
		if ((*world_map_assets)[i].isCollider()) {
			if (Collision::checkBoundingBox(player, &(*world_map_assets)[i])) {

				player->collisionResponse(&(*world_map_assets)[i]);
			}
		}
	}
	

	//collision:: Player <-> fireBall
	std::vector<FireBall>* fireballs = imp_manager.getFireballManager()->getFireBalls();
	for (int i = 0; i < fireballs->size(); i++)
	{
		if ((*fireballs)[i].isAlive()) {
			if (Collision::checkBoundingBox(player, &(*fireballs)[i])) {

				player->collisionResponse(&(*fireballs)[i]);
				(*fireballs)[i].collisionResponse(player);
			}
		}
	}

	//Collision:: Player <-> Imps Sprites
	std::vector<Imp>* imps = imp_manager.getImps();
	for (int i = 0; i < imps->size(); i++) {
		if ((*imps)[i].isAlive()) {
			if (Collision::checkBoundingBox(player, &(*imps)[i].sprite)) {

				player->collisionResponse(&(*imps)[i].sprite);
			}
		}
	}

	// Collisions:: Imps <-> Player
	imp_manager.checkCollisions(player);
	
	if (player->sword.isCollider()) {

		// Collision:: Imps <-> PlayerSword
		imp_manager.checkCollisions(&player->sword);
	}
		

	int viewX = player->getPosition().x;
	if (viewX < map.getPosition().x + view.getSize().x / 2) {

		viewX = map.getPosition().x + view.getSize().x / 2;
	}
	else if (viewX > (map.getPosition().x + map.getMapLength()) - view.getSize().x / 2) {

		viewX = (map.getPosition().x + map.getMapLength()) - view.getSize().x / 2;
	}

	view.setCenter(viewX, player->getPosition().y - 150);


	window->setView(view);

	// Set the Backgrounds at the centre of the new View position
	background->updateTextureCoordinates(dt);
	background->setPosition(view.getCenter().x-view.getSize().x/2, view.getCenter().y-view.getSize().y/2);
	village_bg.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y-village_bg.getSize().y/2);

	
	// Update states
	player->updateState();

	
}

// Render level
void Level::render()
{
	beginDraw();
	

	window->draw(*background);
	window->draw(village_bg);
	map.render(window);
	imp_manager.render(window);
	window->draw(sword_box);
	window->draw(player->sprite);


	endDraw();
	

}
