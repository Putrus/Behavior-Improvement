#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
}


double PhysicsManager::gravity = 0.3;

std::map<std::string, std::vector<float>> PhysicsManager::bounds;
void PhysicsManager::loadCharacterBounds()
{
	std::fstream file("Data/Bounds.txt", std::ios::in);
	std::string name;
	std::string a, b, c, d;
	while (!file.eof())
	{
		//a - ile przesuwamy X b - ile przesuwamy Y, c - ile do sciany w X, d - ile do sciany w Y
		file >> name >> a >> b >> c >> d;
		bounds[name].push_back(std::stof(a));
		bounds[name].push_back(std::stof(b));
		bounds[name].push_back(std::stof(c));
		bounds[name].push_back(std::stof(d));
	}
}

void PhysicsManager::setGravity(double new_gravity)
{
	gravity = new_gravity;
}

double PhysicsManager::getGravity()
{
	return gravity;
}

float PhysicsManager::getBounds(std::string name,int index)
{
	if (index >= name.size() || index <0)
	{
		return -1.f;
	}
	else
	{
		return bounds[name][index];
	}
}


