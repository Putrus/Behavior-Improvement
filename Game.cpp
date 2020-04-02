#include "Game.h"

Game::Game()
{

}

void Game::run()
{

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	Character* hero = new Character("HERO");
	sf::View view(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
	int licznik = 0;
	hero->setPosition(700, 700);
	Platform* platform = new Platform("Platform");
	Platform* platform2 = new Platform("Platform");
	Platform* platform3 = new Platform("Platform");
	Platform* platform4 = new Platform("Platform");
	std::vector<Platform*> * platforms = new std::vector<Platform*>;
	platforms->push_back(platform);
	platforms->push_back(platform2);
	platforms->push_back(platform3);
	platforms->push_back(platform4);
	platform->setPosition(900, 800);
	platform2->setPosition(600, 900);
	platform3->setPosition(900, 300);
	platform4->setPosition(1300, 600);
	window.setFramerateLimit(60);
	
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		hero->control();
		hero->move(platforms);
		if (TimeManager::nextFrame())
		{
			hero->animation();

		}
		window.setView(view);
		window.clear();
		hero->display(window);
		window.draw(*platform);
		window.draw(*platform2);
		window.draw(*platform3);
		window.draw(*platform4);
		window.display();
	}
}







void checkCollision(Character* character, Platform* platform)
{



}