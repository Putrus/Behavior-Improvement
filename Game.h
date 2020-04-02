#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Platform.h"
#include <ctime>


class Game {


private:
	std::map<std::string, sf::FloatRect> collisions;



protected:
public:
	Game();
	void run();
	void checkCollision(Character* character, Platform* platform);


};