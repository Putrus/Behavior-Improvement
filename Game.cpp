#include "Game.h"

Game::Game()
{

}

void Game::run()
{

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	sf::View view(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
	


	Level* level = new Level(0);

	window.setFramerateLimit(60);
	view.setCenter(960, 540);
	Character* hero = new Character("HERO");
	hero->setPosition(50, 70);
	
	Item* item = new Item("Bottle_ordinary");
	
	item->setPosition(500, 80);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		hero->control();
		hero->move(level->getPlatforms());
		item->move(level->getPlatforms());
		view.setCenter(hero->getPosition());
		if (TimeManager::nextFrame())
		{
				hero->animation();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			view.zoom(0.99);
			//hero->setColor(128, 128, 128, 255);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			view.zoom(1.01);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			//level->deletePlatform(1);
			item->throw_(40, -10);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			//level->deletePlatform(1);
			item->throw_(-40, -10);
		}
		window.setView(view);
		window.clear();
		level->displayBackground(window);
		hero->display(window);
		level->displayPlatforms(window);
		item->display(window);
		window.display();
	}
}