#include <SFML/Graphics.hpp>
#include <fstream>

#include "Platform.h"
#include "PhysicsManager.h"


class Level {
private:
	std::vector<Platform*>* platforms;
	std::vector<sf::Sprite*> background_sprites;

	
protected:
public:
	Level(int number);

	~Level();
	void displayBackground(sf::RenderWindow& window);
	void displayPlatforms(sf::RenderWindow& window);

	std::vector<Platform*>* getPlatforms();
	void deletePlatform(int index);
};