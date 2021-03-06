#include "Level.h"

#define PLAYER_BAR_WIDTH 400
#define PLAYER_BAR_HEIGHT 25
#define PLAYER_BAR_BORDER 5

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) :BaseLevel()
{
	level_name = LevelName::LEVEL1;
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;
	view = window->getView();

	// initialise imps
	// Top imps
	imp_manager.spawn(32 *3, -32*16);
	imp_manager.spawn(32 *13, -32*20);
	imp_manager.spawn(32 *23, -32*20);
	imp_manager.spawn(32 *30, -32*17);
	imp_manager.spawn(32 *45, -32*17);
	imp_manager.spawn(32 *47, -32*17);
	imp_manager.spawn(32 *49, -32*17);

	// initial fire imps
	imp_manager.spawn(32 *25, -32*9);
	imp_manager.spawn(32 *36, -32*5);
	imp_manager.spawn(32 *42, -32*5);

	// 
	imp_manager.spawn(32 *101, -32*6);
	imp_manager.spawn(32 *104, -32*11);

	// Jump tower defenders
	imp_manager.spawn(32 *116, -32*15);
	imp_manager.spawn(32 *118, -32*15);

	// mid square imps
	imp_manager.spawn(32 *75, -32*15);
	imp_manager.spawn(32 *80, -32*19);
	imp_manager.spawn(32 *90, -32*14);
	imp_manager.spawn(32 *82, -32*12);

	// right side stacked
	imp_manager.spawn(32 *149, -32*9);
	imp_manager.spawn(32 *149, -32*14);
	imp_manager.spawn(32 *149, -32*18);

	

//	imp_manager.spawn(1150, -300);
	//imp_manager.spawn(1300, -400);

	background = new Background("gfx/MegaBigCloud.png", 0.03f, 2048, 704, 1024);
	background->setSize(sf::Vector2f(1200, 675));

	village_bg_texture.loadFromFile("gfx/town.png");
	village_bg.setTexture(&village_bg_texture);
	village_bg.setSize(sf::Vector2f(1200, 675));
	village_bg.setTextureRect(sf::IntRect(0,0,256,176));
	village_bg.setPosition(0,-675);

	world_map_assets = map.getLevel();

	player = new Player(32*18, -32*9);
	//player = new Player(32*80, -32*9);
	player->setAlive(true);
	player->setInput(input);

	player_health_bar.setSize(sf::Vector2f(PLAYER_BAR_WIDTH, PLAYER_BAR_HEIGHT));
	player_health_bar.setFillColor(sf::Color::Red);
	player_health_bar_border.setSize(sf::Vector2f(PLAYER_BAR_WIDTH + 2 * PLAYER_BAR_BORDER, PLAYER_BAR_HEIGHT + 2* PLAYER_BAR_BORDER));
	player_health_bar_border.setFillColor(sf::Color::Black);

	// Debug sword
	/*sword_box.setSize(sf::Vector2f(player->sword.getSize()));
	sword_box.setFillColor(sf::Color::Blue);*/

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
	else if (input->isKeyDown(sf::Keyboard::O)) {
		gameState->setCurrentState(State::CREDITS_MENU);
	}
	else if (input->isKeyDown(sf::Keyboard::K)) {
		gameState->setCurrentState(State::LOSS_MENU);
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
		

	// Update states
	player->updateState();


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
	int view_left_extend = view.getCenter().x - view.getSize().x / 2;
	int view_top_extend = view.getCenter().y - view.getSize().y / 2;
	background->updateTextureCoordinates(dt);
	background->setPosition(view_left_extend, view_top_extend);
	village_bg.setPosition(view_left_extend, view_top_extend);
	//village_bg.setPosition(view_left_extend, view.getCenter().y-village_bg.getSize().y/2);

	// Update player bar
	player_health_bar_border.setPosition(view_left_extend, view_top_extend);
	player_health_bar.setPosition(view_left_extend + PLAYER_BAR_BORDER, view_top_extend + PLAYER_BAR_BORDER);
	player_health_bar.setSize(sf::Vector2f(player->getHealthPercent() * PLAYER_BAR_WIDTH, PLAYER_BAR_HEIGHT));

}

// Render level
void Level::render()
{
	beginDraw();
	
	// Background
	window->draw(*background);
	window->draw(village_bg);

	// Map
	map.render(window);

	// Characters
	imp_manager.render(window);
	window->draw(player->sprite);

	window->draw(player_health_bar_border);
	window->draw(player_health_bar);
	// Debug
	//window->draw(sword_box);


	endDraw();
	

}
