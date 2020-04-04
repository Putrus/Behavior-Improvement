#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Platform.h"
#include <ctime>
#include "Level.h"
#include "Item.h"
class Game {


private:
	std::map<std::string, sf::FloatRect> collisions;



protected:
public:
	Game();
	void run();

};