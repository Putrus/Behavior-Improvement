#include "Game.h"

Game::Game()
{

}

void Game::run()
{

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	sf::View view(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
	int licznik = 0;
	sf::Color color = sf::Color::Green;
	Platform* platform = new Platform(600, 100, sf::Color::Green);
	Platform* platform2 = new Platform("Platform");
	Platform* platform3 = new Platform(1000,1000);
	std::vector<Platform*> * platforms = new std::vector<Platform*>;
	
	platform->setPosition(400, 800);
	platforms->push_back(platform);

	
	

	platform2->setPosition(100, 500);
	platforms->push_back(platform2);
	platform3->setPosition(20000, 300);
	platforms->push_back(platform3);
	window.setFramerateLimit(60);
	view.setCenter(960, 540);
		Character* hero = new Character("HERO");
		hero->setPosition(500, 500);
		std::vector<sf::RectangleShape> grid;
		for (float i = 0; i < 2160; i += 1920)
		{
			for (float j = 0; j < 3240; j += 1080)
			{
				sf::RectangleShape shape(sf::Vector2f(1920, 1080));
				shape.setOutlineThickness(3);
				shape.setFillColor(sf::Color(128, 128, 0, 255));
				shape.setOutlineColor(sf::Color::Red);
				shape.setPosition(i, j);
				grid.push_back(shape);
			}


		}
	


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
		window.setView(view);
		window.clear();
		for (int i = 0; i < grid.size(); i++)
		{
			window.draw(grid[i]);
		}
		hero->display(window);

		platform->display(window);
		platform2->display(window);
		platform3->display(window);
		
		
		window.display();
	}
}







void checkCollision(Character* character, Platform* platform)
{



}