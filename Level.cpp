#include "Level.h"


Level::Level(int number) {

	this->platforms = new std::vector<Platform*>;
	std::fstream file("Data/Levels/" + std::to_string(number) + ".txt", std::ios::in);
	
	std::string name, temp;
	float gr, s_x, s_y, a, x, y;
	float r, g, b, al;
	int t;
	
		//grawitacja
		file >> temp;
		file >> gr;
		
		PhysicsManager::setGravity(gr / 10);
		
		//rozmiar levela i tlo
		file >> temp;
		file >> s_x >> s_y;
		file >> temp;
		file >> name;
		PhysicsManager::setWalls(0, s_x * 1920, 0, s_y * 1080);
		int i = 0;
		int j = 0;
		for (i = 0; i < s_x; i++)
		{
			//obramowanie
			sf::Sprite* sprite = new sf::Sprite();
			sprite->setTexture(*TextureManager::getTexture(name + ".png"));
			sprite->setTextureRect(sf::IntRect(0, 0, 1960, 40));
			
			for (j = 0; j < s_y; j++)
			{
				//tlo
				sf::Sprite* sprite = new sf::Sprite();
				sprite->setTexture(*TextureManager::getTexture(name + "en.png"));
				sprite->setPosition(i * 1920, j * 1080);
				this->background_sprites.push_back(sprite);

				if (i == 0)
				{
					sf::Sprite* sprite = new sf::Sprite();
					sprite->setTexture(*TextureManager::getTexture(name + ".png"));
					sprite->setTextureRect(sf::IntRect(0, 0, 40, 1120));
					sprite->setPosition(-40, j * 1080 - 20);
					this->background_sprites.push_back(sprite);
				}
				if (i == s_x - 1)
				{
					sf::Sprite* sprite = new sf::Sprite();
					sprite->setTexture(*TextureManager::getTexture(name + ".png"));
					sprite->setTextureRect(sf::IntRect(0, 0, 40, 1120));
					sprite->setScale(-1, 1);
					sprite->setPosition(s_x * 1920 + 40, j * 1080 - 20);
					this->background_sprites.push_back(sprite);
				}
			}
			sf::Sprite* sprite2 = new sf::Sprite();
			sprite2->setTexture(*TextureManager::getTexture(name + ".png"));
			sprite2->setTextureRect(sf::IntRect(0, 0, 1960, 40));
			sprite2->setScale(1, -1);
			if (i == s_x - 1)
			{
				sprite->setPosition(i * 1920, -40);
				sprite2->setPosition(i * 1920, s_y * 1080 + 40);
			}
			else
			{
				sprite->setPosition(i * 1920 - 40, -40);
				sprite2->setPosition(i * 1920 - 40, s_y * 1080 + 40);

			}
			this->background_sprites.push_back(sprite);
			this->background_sprites.push_back(sprite2);
		}
		
		//platformy
		file >> temp;
		while(!file.eof())
		{
			//g jako typ
			file >> gr;
			if (gr == 0)
			{
				file >> s_x >> s_y >> x >> y;
				Platform* platform = new Platform(s_x, s_y);
				platform->setPosition(x, y);
				this->platforms->push_back(platform);
			}
			if (gr == 1)
			{
				file >> s_x >> s_y >> r >> g >> b >> al >> x >> y;
				Platform* platform = new Platform(s_x, s_y, sf::Color(r, g, b, al));
				platform->setPosition(x, y);
				this->platforms->push_back(platform);
			}
			if (gr == 2)
			{
				file >> name >> t >>  x >> y;
				std::cout << name << " " << t << " " << x << " " << y << std::endl;
				Platform* platform = new Platform(name,t);
				platform->setPosition(x, y);
				this->platforms->push_back(platform);
			}
			

		}

		file.close();
}





Level::~Level()
{
	for (std::vector<sf::Sprite*>::iterator it; it < this->background_sprites.begin(); it++)
	{
		delete *it;
	}
	for (std::vector<Platform*>::iterator it; it < this->platforms->begin(); it++)
	{
		delete* it;
	}
	delete this->platforms;
}




void Level::displayBackground(sf::RenderWindow& window)
{
	for (std::vector<sf::Sprite*>::iterator it = this->background_sprites.begin(); it != this->background_sprites.end(); it++)
	{
		window.draw(**it);

	}



}
void Level::displayPlatforms(sf::RenderWindow& window)
{
	{
		for (std::vector<Platform*>::iterator it = this->platforms->begin(); it != this->platforms->end(); it++)
		{
			(*it)->display(window);
		}
	}
}




std::vector<Platform*>* Level::getPlatforms()
{
	return this->platforms;
}

void Level::deletePlatform(int index)
{
	if (index < platforms->size())
	{
		this->platforms->erase(platforms->begin() + index);
	}
}