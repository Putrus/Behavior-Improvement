#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
}


double PhysicsManager::gravity = 0.3;

float PhysicsManager::leftWall = 0;
float PhysicsManager::rightWall = 1920;
float PhysicsManager::upWall = 0;
float PhysicsManager::downWall = 1080;

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
	file.close();
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


void PhysicsManager::setWalls(float l, float r, float u, float d)
{
	leftWall = l;
	rightWall = r;
	upWall = u;
	downWall = d;


}


float PhysicsManager::getLeftWall()
{
	return leftWall;
}

float PhysicsManager::getRightWall()
{
	return rightWall;
}

float PhysicsManager::getUpWall()
{
	return upWall;
}

float PhysicsManager::getDownWall()
{
	return downWall;
}