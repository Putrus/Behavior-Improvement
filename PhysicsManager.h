#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>

#include "Platform.h"
class PhysicsManager {
private:
	PhysicsManager();
	static double gravity;
	static std::map<std::string, std::vector<float>> bounds;

	static float leftWall;
	static float rightWall;
	static float upWall;
	static float downWall;
public:
	static void setGravity(double new_gravity);
	static void loadCharacterBounds();
	static double getGravity();
	static float getBounds(std::string name, int index);
	static void setWalls(float l, float r, float u, float d);
};