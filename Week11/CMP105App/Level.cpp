#include "Level.h"

//sf::View* Level::view = nullptr;

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) :BaseLevel()
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	//Loading player spritesheet
	

	level_name = LevelName::LEVEL1;
	// initialise game objects
	imp_manager.spawn(512, -110);
	imp_manager.spawn(1150, -300);
	imp_manager.spawn(1300, -400);

	background = new Background("gfx/MegaBigCloud.png", 0.03f, 2048, 704, 1024);
	background->setSize(sf::Vector2f(1200, 675));

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
	player->setAlive(true);
	player->setInput(input);

	

	sword_box.setSize(sf::Vector2f(player->sword.getSize()));
	sword_box.setFillColor(sf::Color::Blue);
}

Level::~Level()
{
	//Manually destroying pointers
	delete player;
	delete background;
	enemies.clear();
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
	// Update the characters
	player->update(dt);
	imp_manager.update(dt);

	// COLLISION HANDLING
	// Collisions:: Player <-> map
	for (int i = 0; i < world_map->size(); i++){
		if ((*world_map)[i].isCollider()) {
			if (Collision::checkBoundingBox(player, &(*world_map)[i])) {

				player->collisionResponse(&(*world_map)[i]);
			}
		}
	}
	if (player->isAlive()) {

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
	}
	if (player->sword.isCollider()) {

		// Collision:: Imps <-> PlayerSword
		imp_manager.checkCollisions(&player->sword);
	}
		




	/*for (int i = 0; i < enemies.size(); i++)
	{
		if (Collision::checkBoundingBox(player, &(enemies[i]))) {
			enemies[i].collisionResponse(player);
		}
		if (player->sword.isCollider()) {
			if (player->sword.collision_layer == CollisionLayer::SWORD) {
				std::cout << "I AM A SWORD" << std::endl;
			}
			std::cout << "I CAN CUT" << std::endl;
			if (Collision::checkBoundingBox(&player->sword, &enemies[i].sprite)) {
				std::cout << "I HAVE CUT IMP" << std::endl;
				enemies[i].collisionResponse(&player->sword);
			}
		}
	}*/
	

	// Set View position depending on the Player position
	if (player->getPosition().x <= view.getSize().x/2) {
		view.setCenter(view.getCenter().x, player->getPosition().y - 150);
	}
	else {
		view.setCenter(player->getPosition().x, player->getPosition().y - 150);
	}
	window->setView(view);

	// Set the Backgrounds at the centre of the new View position
	background->updateTextureCoordinates(dt);
	background->setPosition(view.getCenter().x-view.getSize().x/2, view.getCenter().y-view.getSize().y/2);
	layer2.setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y-layer2.getSize().y/2);

	
	// Update states
	player->updateState();
}

// Render level
void Level::render()
{
	beginDraw();
	

	window->draw(*background);
	window->draw(layer2);
	map.render(window);
	imp_manager.render(window);
	window->draw(sword_box);
	window->draw(player->sprite);


	endDraw();
	

}

