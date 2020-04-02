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
	this->sprite->setOrigin(PhysicsManager::getBounds(this->name,0), PhysicsManager::getBounds(this->name,1));
	this->bound_x = PhysicsManager::getBounds(this->name, 2);
	this->bound_y = PhysicsManager::getBounds(this->name, 3);

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
		this->animation_y = 256;
	}
	else
	{
		this->animation_y = 0;
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
void Character::gravity(float ground)
{
	if (this->getPosition().y < ground)
	{
		std::cout << "ground: " << ground << std::endl;
		this->in_air = true;
		this->speed_y += PhysicsManager::getGravity();
		if ((this->getPosition().y + this->bound_y) > ground)
		{
			
			this->speed_y = 0;
			this->setPosition(this->getPosition().x, ground - this->bound_y);
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
	this->gravity(this->calcWalls(platforms)[0]);
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


float* Character::calcWalls(std::vector<Platform*> *platforms)
{
	float result[4] = { 1080, 0,1920,-200};
	
	
	for (std::vector<Platform*>::iterator it = platforms->begin(); it != platforms->end(); it++)
	{

		//sprawdzanie najmniejszej odleglosci i innych wlasciwosci - czy dana platforma to spelnia result[0] - sciana dolna
		if (((this->getPosition().y + this->bound_y) < (*it)->getGlobalBounds().top+ (*it)->getGlobalBounds().height/2) && ((this->getPosition().x -this->bound_x)< ((*it)->getGlobalBounds().left + (*it)->getGlobalBounds().width)) && ((this->getPosition().x +this->bound_x) > ((*it)->getGlobalBounds().left)) &&  (((*it)->getGlobalBounds().top - (this->getPosition().y + this->bound_y)) <= (result[0] - (this->getPosition().y + this->bound_y))))
		{
			result[0] = (*it)->getGlobalBounds().top;
		}
		

	}
	

	return result;

}

