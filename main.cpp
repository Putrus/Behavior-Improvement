#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
	int main()
	{

		
		
		TextureManager::loadAllTextures();
		PhysicsManager::loadCharacterBounds();
		Game* game = new Game();
		game->run();
		return 0;
	}
