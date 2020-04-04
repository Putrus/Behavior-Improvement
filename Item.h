#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "TextureManager.h"
#include "Platform.h"
#include "PhysicsManager.h"
class Item {
private:
	std::string name;
	int id;
	sf::Sprite* sprite;
	std::vector<float> walls;
	bool in_air;

	float speed_x;
	float speed_y;
protected:
public:
	Item(std::string name);

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();


	void gravity();
	void calcWalls(std::vector<Platform*>* platforms);
	void checkCollision();

	void display(sf::RenderWindow& window);

	void move(std::vector<Platform*>* platforms);

	void throw_(float sx, float sy);

	void stayStill();
};