#include "Item.h"


Item::Item(std::string name)
{
	this->sprite = new sf::Sprite();
	this->speed_x = 0;
	this->speed_y = 0;
	std::fstream file("Data/Items.txt", std::ios::in);
	
	this->sprite->setTexture(*TextureManager::getTexture("Item.png"));
	this->name = name;
	std::string n;
	int i, x, y, s_x, s_y;
	while (!file.eof())
	{
		file >> i >> n >> x >> y >> s_x >> s_y;
		if (n == name)
		{
			this->id = i;
			this->sprite->setTextureRect(sf::IntRect(x, y, s_x, s_y));
		}
	}

	this->in_air = false;
	this->walls.push_back(1080.f);
	this->walls.push_back(0.f);
	this->walls.push_back(1920.f);
	this->walls.push_back(0.f);
}



void Item::setPosition(float x, float y)
{
	this->sprite->setPosition(x, y);


}
void Item::setPosition(sf::Vector2f position)
{
	this->sprite->setPosition(position);
}
sf::Vector2f Item::getPosition()
{
	return this->sprite->getPosition();
}




void Item::gravity()
{
	if (this->getPosition().y != this->walls[0] - this->sprite->getLocalBounds().height)
	{
		this->in_air = true;
		this->speed_y += PhysicsManager::getGravity();
		if ((this->getPosition().y + this->sprite->getLocalBounds().height) >= this->walls[0])
		{
			this->speed_y = 0;
			this->setPosition(this->getPosition().x, this->walls[0] - this->sprite->getLocalBounds().height);
			this->in_air = false;
		}
	}
}






void Item::calcWalls(std::vector<Platform*>* platforms)
{
	this->walls[0] = PhysicsManager::getDownWall();
	this->walls[1] = PhysicsManager::getLeftWall();
	this->walls[2] = PhysicsManager::getRightWall();
	this->walls[3] = PhysicsManager::getUpWall();

	float cl, cr, cu, cd;
	cl = this->getPosition().x;
	cr = this->getPosition().x + this->sprite->getLocalBounds().width;
	cu = this->getPosition().y;
	cd = this->getPosition().y + this->sprite->getLocalBounds().height;
	float pl, pr, pu, pd;
	for (std::vector<Platform*>::iterator it = platforms->begin(); it != platforms->end(); it++)
	{

		pl = (*it)->getGlobalBounds().left;
		pr = (*it)->getGlobalBounds().left + (*it)->getGlobalBounds().width;
		pu = (*it)->getGlobalBounds().top;
		pd = (*it)->getGlobalBounds().top + (*it)->getGlobalBounds().height;

		//sprawdzanie najmniejszej odleglosci i innych wlasciwosci - czy dana platforma to spelnia result[0] - sciana dolna
		if ((cd < pu + this->speed_y * 2 + 1) && (cl < pr) && (cr > pl) && (pu < this->walls[0]))
		{
			this->walls[0] = pu;

		}

		if ((cl > pr) && (pr > this->walls[1]) && ((cu >= pu && cu <= pd) || (cd >= pu && cd <= pd) || (cu <= pu && cd >= pd)))
		{
			this->walls[1] = pr;

		}
		if ((cr < pl) && (pl < this->walls[2]) && ((cu > pu&& cu < pd) || (cd > pu&& cd < pd) || (cu <= pu && cd >= pd)))
		{
			this->walls[2] = pl;

		}
		if ((cu >= pd) && (cl < pr) && (cr > pl) && (pd > this->walls[3]))
		{
			this->walls[3] = pd;
		}

	}
	std::cout << walls[3] << std::endl;
}
void Item::checkCollision()
{
	if ((this->getPosition().x ) < walls[1] - 2 * this->speed_x + 1)
	{
		this->setPosition(this->walls[1] + this->sprite->getLocalBounds().width- 2 * this->speed_x + 1, this->getPosition().y);
	}

	if ((this->getPosition().x + this->sprite->getLocalBounds().width) > walls[2] - 2 * this->speed_x - 1)
	{
		this->setPosition(this->walls[2] - this->sprite->getLocalBounds().width - 2 * this->speed_x - 1, this->getPosition().y);
	}
	if ((this->getPosition().y) < this->walls[3] - speed_y)
	{
		this->speed_y = 0;
		this->setPosition(this->getPosition().x, this->walls[3] + this->sprite->getLocalBounds().height + 1);
	}

}

void Item::display(sf::RenderWindow& window)
{
	window.draw(*this->sprite);
}




void Item::move(std::vector<Platform*>* platforms)
{
	this->calcWalls(platforms);
	this->gravity();
	this->checkCollision();
	this->stayStill();
	this->setPosition(this->getPosition().x + this->speed_x, this->getPosition().y + this->speed_y);
}


void Item::throw_(float sx, float sy)
{
	this->speed_x = sx;
	this->speed_y = sy;
}


void Item::stayStill()
{
	if (this->speed_x > 0)
	{
		this->speed_x--;
	}
	else if (this->speed_x < 0)
	{
		this->speed_x++;
	}
	else
	{
		this->speed_x = 0;
	}

}