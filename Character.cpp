#include "Character.h"

//konstruktor
Character::Character(std::string name)
{
	this->sprite = new sf::Sprite();
	this->name = name;
	this->sprite->setTexture(*TextureManager::getTexture(name + ".png"));
	this->animation_x = 0;
	this->animation_y = 0;
	this->speed_x = 0;
	this->speed_y = 0;
	this->sprite->setTextureRect(sf::IntRect(0, 0, 256, 256));
	this->in_air = false; 
	this->sprite->setOrigin(PhysicsManager::getBounds(this->name, 0), PhysicsManager::getBounds(this->name, 1));
	this->bound_x = PhysicsManager::getBounds(this->name, 2);
	this->bound_y = PhysicsManager::getBounds(this->name, 3);
	this->walls.push_back(1080.f);
	this->walls.push_back(0.f);
	this->walls.push_back(1920.f);
	this->walls.push_back(0.f);
}


//wyswietlanie postaci
void Character::display(sf::RenderWindow& window)
{
	window.draw(*this->sprite);
}



//animacja - jeszcze moze poprawie aby kazda animacja miala 12 klatek/sekunda
void Character::animation()
{

	if (this->speed_x != 0)
	{
		this->animation_y = 768;
	}
	else
	{
		this->animation_y = 512;
	}


	this->animation_x += 256;
	if(this->animation_x == 3072)
	{
		animation_x = 0;
	}
		this->sprite->setTextureRect(sf::IntRect(this->animation_x, this->animation_y, 256, 256));
}

void Character::setPosition(float x, float y)
{
	this->sprite->setPosition(x, y);
}

sf::Vector2f Character::getPosition()
{
	return this->sprite->getPosition();
}


void Character::moveRight()
{
	this->turn(true);
	if (this->speed_x < 6)
	{
		this->speed_x += 1;
	}
}
void Character::moveLeft()
{
	this->turn(false);
	if (this->speed_x > -6)
	{
		this->speed_x -= 1;
	}
}

void Character::stayStill()
{
	if (this->speed_x > 0)
	{
		this->speed_x--;
	}
	else if(this->speed_x <0)
	{
		this->speed_x++;
	}
	else
	{
		this->speed_x = 0;
	}
	
}

void Character::jump()
{
	if (this->in_air == false)
	{
		this->speed_y = -15;
		this->in_air = true;
	}
	}

//funkcja sprawdzajaca czy jest w powietrzu i jesli tak to gdzie ma spasc - grawitacja
void Character::gravity()
{
	if (this->getPosition().y != this->walls[0] - this->bound_y)
	{
		this->in_air = true;
		this->speed_y += PhysicsManager::getGravity();
		if ((this->getPosition().y + this->bound_y) >= this->walls[0])
		{
			this->speed_y = 0;
			this->setPosition(this->getPosition().x, this->walls[0] - this->bound_y);
			this->in_air = false;
		}
	}
}





//zawracanie
void Character::turn(bool right)
{
	if (right)
	{
		
		this->sprite->setScale(1, 1);
		
	}
	else
	{
		this->sprite->setScale(-1, 1);
		
	}
}

void Character::move(std::vector<Platform*> *platforms)
{
	this->calcWalls(platforms);
	this->gravity();
	this->checkCollision();
	
	this->setPosition(this->getPosition().x + this->speed_x, this->getPosition().y+this->speed_y);
	
}



void Character::control()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->moveRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->moveLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->jump();
	}

	if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		this->stayStill();
	}
	
}
void Character::calcWalls(std::vector<Platform*> *platforms)
{
	this->walls[0] = PhysicsManager::getDownWall();
	this->walls[1] = PhysicsManager::getLeftWall();
	this->walls[2] = PhysicsManager::getRightWall();
	this->walls[3] = PhysicsManager::getUpWall();
	
	float cl, cr, cu, cd;
	cl = this->getPosition().x - this->bound_x;
	cr = this->getPosition().x + this->bound_x;
	cu = this->getPosition().y - this->bound_y;
	cd = this->getPosition().y + this->bound_y;
	float pl, pr, pu, pd;
	for (std::vector<Platform*>::iterator it = platforms->begin(); it != platforms->end(); it++)
	{
			
		pl = (*it)->getGlobalBounds().left;
		pr = (*it)->getGlobalBounds().left + (*it)->getGlobalBounds().width;
		pu = (*it)->getGlobalBounds().top;
		pd = (*it)->getGlobalBounds().top + (*it)->getGlobalBounds().height;

		//sprawdzanie najmniejszej odleglosci i innych wlasciwosci - czy dana platforma to spelnia result[0] - sciana dolna
		if ((cd < pu + this->speed_y * 2 + 1) && (cl < pr) && (cr > pl) &&  (pu < this->walls[0]))
		{
			this->walls[0] = pu;
			
		}
	
		if ((cl > pr) && (pr  >  this->walls[1]) && ((cu >= pu && cu <= pd) || (cd >= pu && cd <= pd) || (cu <= pu && cd >= pd)))
		{
			this->walls[1] = pr;
			
		}
		if ((cr < pl) && (pl  < this->walls[2]) && ((cu > pu&& cu < pd) || (cd > pu&& cd < pd) || (cu <= pu && cd >= pd)))
		{
			this->walls[2] = pl;
			
		}
		if ((cu >= pd)  && (cl < pr) && (cr > pl) && (pd > this->walls[3]))
		{
			this->walls[3] = pd;
		}
		
	}
}
void Character::checkCollision()
{
		if ((this->getPosition().x - this->bound_x) < walls[1]-2*this->speed_x+1)
		{
			this->setPosition(this->walls[1] + this->bound_x - 2 * this->speed_x + 1, this->getPosition().y );
		}
		
		if ((this->getPosition().x + this->bound_x) > walls[2] - 2 * this->speed_x - 1)
		{
			this->setPosition(this->walls[2] - this->bound_x - 2 * this->speed_x - 1, this->getPosition().y);
		}
		if ((this->getPosition().y - this->bound_y) < this->walls[3] - speed_y)
		{
			this->speed_y = 0;
			this->setPosition(this->getPosition().x, this->walls[3] + this->bound_y+1);
		}

	}



void Character::setColor(float r, float g, float b, float a)
{
	this->sprite->setColor(sf::Color(r, g, b, a));
}